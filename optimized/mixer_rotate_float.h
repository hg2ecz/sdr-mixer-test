#include <complex.h>

struct _mixer_rotate_float {
    complex float osc;
    complex float phase;
};

void mixer_init_rotate_float(struct _mixer_rotate_float *mixer_rotate_float, double freq, unsigned int samplerate);
void mixer_mix_rotate_float(complex float *sampleout, const complex float *samplein, struct _mixer_rotate_float *mixer_rotate_float, int samplelen4);
