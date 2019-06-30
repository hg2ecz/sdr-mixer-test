#include <math.h>
#include "mixer_rotate.h"

void mixer_init_rotate(struct _mixer_rotate *mixer_rotate, double freq, unsigned int samplerate) {
    double phase_radian = 2*M_PI*freq/samplerate;
    mixer_rotate->osc = 1. + 0.j;
    mixer_rotate->phase = cos(phase_radian) + sin(phase_radian)*1.j;
}

void mixer_mix_rotate(complex float *sampleout, const complex float *samplein, struct _mixer_rotate *mixer_rotate, int samplelen) {
    complex double       osc   = mixer_rotate->osc;             // register -> faster
    const complex double phase = mixer_rotate->phase;           // register -> faster

    for (int i=0; i<samplelen; i++) {
        sampleout[i] = samplein[i] * (complex float)osc; // mixing
        osc *= phase;                                    // next oscillator state
    }

    mixer_rotate->osc = osc;                                    // store back from register
}
