#include <math.h>
#include "mixer_rotate_float.h"

void mixer_init_rotate_float(struct _mixer_rotate_float *mixer_rotate_float, double freq, unsigned int samplerate) {
    double phase_radian = 2*M_PI*freq/samplerate;
    mixer_rotate_float->osc = 1. + 0.j;
    mixer_rotate_float->phase = cos(phase_radian) + sin(phase_radian)*1.j;
}

void mixer_mix_rotate_float(complex float *sampleout, const complex float *samplein, struct _mixer_rotate_float *mixer_rotate_float, int samplelen) {
    complex float       osc   = mixer_rotate_float->osc;    // register -> faster
    const complex float phase = mixer_rotate_float->phase;  // register -> faster

    for (int i=0; i<samplelen; i++) {
        sampleout[i] = samplein[i] * osc;                // mixing
        osc *= phase;                                    // next oscillator state
    }

    mixer_rotate_float->osc = osc;                       // store back from register
}
