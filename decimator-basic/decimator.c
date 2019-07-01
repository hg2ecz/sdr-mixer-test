#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include "decimator.h"

void mixer_init(struct _mixer *mixer, double freq, unsigned int samplerate) {
    double phase_radian = 2*M_PI*freq/samplerate;
    mixer->osc = 1. + 0.j;
    mixer->phase = cos(phase_radian) + sin(phase_radian)*1.j;
}

void mixer(complex float *sampleout, const complex float *samplein, struct _mixer *mixer, int samplelen) {
    complex double       osc   = mixer->osc;             // register -> faster
    const complex double phase = mixer->phase;           // register -> faster

    for (int i=0; i<samplelen; i++) {
        sampleout[i] = samplein[i] * (complex float)osc; // mixing
        osc *= phase;                                    // next oscillator state
    }

    mixer->osc = osc;                                    // store back from register
}

// transition_bw: 0.05
static void calc_coeff(struct _decimstate *ds, float cutoff_rate, float transition_bw, enum Window window) {
    int taps_len=((int)(4.0/transition_bw + 0.5)) | 1; // odd
    int middle=taps_len/2;

    float *firtaps = ds->coeff_noncomplex;
    ds->coefflen = taps_len;

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
int decimator_init(struct _decimstate *ds, unsigned int mixfreq, unsigned int samplerate, unsigned int decimfactor,
                       float transition_bw, enum Window window) {

    if (mixfreq != 0) { // mixer
        ds->is_mix = 1;
        mixer_init(&ds->mixer, mixfreq, samplerate);
    } else {
        ds->is_mix = 0;
    }

    ds->samplelen = 0;
    ds->decimfactor = decimfactor;
    calc_coeff(ds, 1./decimfactor, transition_bw, window);

    fprintf(stderr, "coefflen4: %d * 4\n", ds->coefflen);
    return 0;
}

int decimator(complex float *sampleout, const complex float *samplein, struct _decimstate *ds, int sampleinlen) {
    // mixcopy or simple copy?
    if (ds->is_mix) { // mix
        mixer(&ds->sample[ds->samplelen], samplein, &ds->mixer, sampleinlen);
    } else { // not mit --> memcopy
        memcpy(&ds->sample[ds->samplelen], samplein, &samplein[sampleinlen]-samplein);
    }
    ds->samplelen += sampleinlen;
    // decimate
    int j, k=0;
    for (j=0; j <= ds->samplelen - ds->coefflen - ds->decimfactor; j+= ds->decimfactor) {
        complex float tmp = 0.;

        for (int i=0; i < ds->coefflen; i++) {
            //tmp += ds->sample[i + j] * ds->coeff[i]
            tmp += ds->sample[i + j] * ds->coeff_noncomplex[i];
        }
        sampleout[k++] = tmp;

    }
    int pos = j;
    memmove(ds->sample, &ds->sample[pos], &ds->sample[ds->samplelen] - &ds->sample[pos]);
    ds->samplelen-=pos;
    return k; // return outlen
}
