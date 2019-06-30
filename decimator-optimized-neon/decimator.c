#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include "decimator.h"

static int fastmixer_init(struct _mixer *mixer, unsigned int mixfreq, unsigned int samplerate) {
    float phase_radian = 2.*M_PI*mixfreq/samplerate;
    mixer->osc_re[0] = cosf(0.*phase_radian);
    mixer->osc_re[1] = cosf(1.*phase_radian);
    mixer->osc_re[2] = cosf(2.*phase_radian);
    mixer->osc_re[3] = cosf(3.*phase_radian);

    mixer->osc_im[0] = sinf(0.*phase_radian);
    mixer->osc_im[1] = sinf(1.*phase_radian);
    mixer->osc_im[2] = sinf(2.*phase_radian);
    mixer->osc_im[3] = sinf(3.*phase_radian);

    float phase_re = cosf(4.*phase_radian);
    mixer->phase_re[0] = phase_re;
    mixer->phase_re[1] = phase_re;
    mixer->phase_re[2] = phase_re;
    mixer->phase_re[3] = phase_re;

    float phase_im = sinf(4.*phase_radian);
    mixer->phase_im[0] = phase_im;
    mixer->phase_im[1] = phase_im;
    mixer->phase_im[2] = phase_im;
    mixer->phase_im[3] = phase_im;

    return 0;
}

static void fastmixer(float *sout_re, float *sout_im, const float *sinp_re, const float *sinp_im, struct _mixer *mixer, int len) {
    if ((len & 3) != 0) {
        fprintf(stderr, "Input sample len must multiple of 4 float.\n");
        exit(-1);
    }
    VECTYPE osc_re = mixer->osc_re;      // register -> faster
    VECTYPE osc_im = mixer->osc_im;
    VECTYPE phase_re = mixer->phase_re;  // register -> faster
    VECTYPE phase_im = mixer->phase_im;

    for (int i=0; i<len; i+=4) {
        VECTYPE s_in_re = *((VECTYPE *)&sinp_re[i]);
        VECTYPE s_in_im = *((VECTYPE *)&sinp_im[i]);

        VECTYPE *s_out_re = (VECTYPE *)&sout_re[i];
        VECTYPE *s_out_im = (VECTYPE *)&sout_im[i];

        *s_out_re = s_in_re * osc_re - s_in_im * osc_im;
        *s_out_im = s_in_re * osc_im + s_in_im * osc_re;

        VECTYPE osc_re_tmp = osc_re;
        osc_re = osc_re_tmp * phase_re - osc_im * phase_im;
        osc_im = osc_re_tmp * phase_im + osc_im * phase_re;
    }

    mixer->osc_re = osc_re;                       // store back from register
    mixer->osc_im = osc_im;                       // store back from register
}

// transition_bw: 0.05
static void calc_coeff(struct _decimstate *ds, float cutoff_rate, float transition_bw, enum Window window) {
    int taps_len=((int)(4.0/transition_bw + 0.5)) | 1; // odd
    int middle=taps_len/2;

    float *firtaps = (float *)ds->coeff_noncomplex;
    ds->coefflen4 = (taps_len + 3)/4;
    if (ds->coefflen4 > 0) {
        ds->coeff_noncomplex[ds->coefflen4 - 1][0] = 0.;
        ds->coeff_noncomplex[ds->coefflen4 - 1][1] = 0.;
        ds->coeff_noncomplex[ds->coefflen4 - 1][2] = 0.;
        ds->coeff_noncomplex[ds->coefflen4 - 1][3] = 0.;
    }

    float sum=0.;
    float wfuncval;
    for (int i=1; i<= middle; i++) {
        float rate = (float)i / middle / 2. + 0.5;

        switch (window) {
            case Blackman:
                wfuncval = 0.42-0.5*cos(2.*M_PI*rate) + 0.08*cos(4.*M_PI*rate);
                break;
            case Hamming:
                wfuncval = 0.54-0.46*cos(2.*M_PI*rate);
                break;
            default:
                puts("Bad filter type.");
                exit(-1);
                break;
        }

        firtaps[middle+i] = firtaps[middle-i] = sin(2.*M_PI*cutoff_rate*i) / i * wfuncval;
        sum += firtaps[middle-i] + firtaps[middle+i];
    }
    for (int i=0; i<taps_len; i++) {
        firtaps[i] /= sum;
    }
    fprintf(stderr, "taps_len: %d\n", taps_len);
}

// transition_bw: 0.05
int fastdecimator_init(struct _decimstate *ds, unsigned int mixfreq, unsigned int samplerate, unsigned int decimfactor,
                       float transition_bw, enum Window window) {

    if (mixfreq != 0) { // mixer
        ds->is_mix = 1;
        fastmixer_init(&ds->mixer, mixfreq, samplerate);
    } else {
        ds->is_mix = 0;
    }

    ds->samplelen = 0;
    ds->decimfactor = decimfactor;
    calc_coeff(ds, 1./decimfactor, transition_bw, window);

    fprintf(stderr, "coefflen4: %d * 4\n", ds->coefflen4);
    return 0;
}

int fastdecimator(struct _sample *sampleout, const struct _sample *samplein, struct _decimstate *ds) {
    // mixcopy or simple copy?
    if (ds->is_mix) { // mix
        fastmixer(&ds->sample_re[ds->samplelen], &ds->sample_im[ds->samplelen], samplein->re, samplein->im, &ds->mixer, samplein->len/4);
    } else { // not mit --> memcopy
        memcpy(&ds->sample_re[ds->samplelen], samplein->re, &samplein->re[samplein->len]-samplein->re);
        memcpy(&ds->sample_im[ds->samplelen], samplein->im, &samplein->im[samplein->len]-samplein->im);
    }
    ds->samplelen += samplein->len;
    // decimate
    int j, k=0;
    for (j=0; j <= ds->samplelen - 4*ds->coefflen4 - ds->decimfactor; j+= ds->decimfactor) {
        VECTYPE tmp_re = {0., 0., 0., 0.};
        VECTYPE tmp_im = {0., 0., 0., 0.};
        for (int i=0; i < ds->coefflen4; i++) {
            VECTYPE s_re = *((VECTYPE *)&ds->sample_re[4*i + j]);
            VECTYPE s_im = *((VECTYPE *)&ds->sample_im[4*i + j]);

            //tmp_re += s_re * ds->coeff_re[i] - s_im * ds->coeff_im[i];
            //tmp_im += s_re * ds->coeff_im[i] + s_im * ds->coeff_re[i];
            tmp_re += s_re * ds->coeff_noncomplex[i];
            tmp_im += s_im * ds->coeff_noncomplex[i];
        }
        sampleout->re[k] = tmp_re[3]+tmp_re[2]+tmp_re[1]+tmp_re[0];
        sampleout->im[k] = tmp_im[3]+tmp_im[2]+tmp_im[1]+tmp_im[0];
        k++;
    }
    int pos = j;
    memmove(ds->sample_re, &ds->sample_re[pos], &ds->sample_re[pos] - ds->sample_re);
    memmove(ds->sample_im, &ds->sample_im[pos], &ds->sample_re[pos] - &ds->sample_re[pos]);
    ds->samplelen-=pos;
    sampleout->len = k;
    return 0;
}
