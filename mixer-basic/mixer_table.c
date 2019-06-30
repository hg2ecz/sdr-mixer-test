#include <stdio.h>
#include <stdlib.h>

#include <math.h>
#include "mixer_table.h"

void mixer_init_table(struct _mixer_table *mixer_table, double freq, unsigned int samplerate) {
    double ratio = (double)samplerate / freq;
    if (ratio != floor(ratio) || ratio > MAXMIXTABLE) {
        fprintf(stderr, "Error: mixer ratio\n");
        exit(-1);
    }
    mixer_table->len=ratio;
    for (int i=0; i<mixer_table->len; i++) {
        double phase_radian = i*2*M_PI*freq/samplerate;
        mixer_table->mix[i] = cos(phase_radian) + sin(phase_radian)*1.j;
    }
    mixer_table->actpos=0;
}

void mixer_mix_table(complex float *sampleout, const complex float *samplein, struct _mixer_table *mixer_table, int samplelen) {
    complex float *mix = mixer_table->mix;
    int mpos=mixer_table->actpos;                 // register -> faster

    for (int i=0; i<samplelen; i++) {
        sampleout[i] = samplein[i] * mix[mpos++]; // mixing
        if (mpos == mixer_table->len) mpos=0;
    }

    mixer_table->actpos = mpos;                   // store back from register
}
