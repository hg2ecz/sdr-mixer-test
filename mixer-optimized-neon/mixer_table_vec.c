#include <stdio.h>
#include <stdlib.h>

#include <math.h>
#include "mixer_table_vec.h"

void mixer_init_table_vec(struct _mixer_table_vec *mixer_table_vec, double freq, unsigned int samplerate) {
    double ratio = (double)samplerate / freq;
    if (ratio != floor(ratio) || ratio > MAXMIXTABLE-1) {
        fprintf(stderr, "Error: mixer ratio\n");
        exit(-1);
    }
    mixer_table_vec->len4=ratio;
    for (int i=0; i<4*mixer_table_vec->len4; i++) { // compare only every 4. th. See below
        double phase_radian = i*2*M_PI*freq/samplerate;
        mixer_table_vec->mix_re[i/4][i%4] = cos(phase_radian);
        mixer_table_vec->mix_im[i/4][i%4] = sin(phase_radian);
    }
    mixer_table_vec->actpos4=0;
}

void mixer_mix_table_vec(struct _sample *sampleout, const struct _sample *samplein, struct _mixer_table_vec *mixer_table_vec) {
    VECTYPE *mix_re = mixer_table_vec->mix_re;
    VECTYPE *mix_im = mixer_table_vec->mix_im;
    int mpos=mixer_table_vec->actpos4;                 // register -> faster

    for (int i=0; i<4*SAMPLELEN4; i+=4) {
        VECTYPE s_in_re = *((VECTYPE *)&samplein->re[i]);
        VECTYPE s_in_im = *((VECTYPE *)&samplein->im[i]);

        VECTYPE *s_out_re = (VECTYPE *)&sampleout->re[i];
        VECTYPE *s_out_im = (VECTYPE *)&sampleout->im[i];

        *s_out_re = s_in_re * mix_re[mpos] - s_in_im * mix_im[mpos];
        *s_out_im = s_in_re * mix_im[mpos] + s_in_im * mix_re[mpos];

        if (++mpos == mixer_table_vec->len4) mpos=0;
    }

    mixer_table_vec->actpos4 = mpos;                   // store back from register
}
