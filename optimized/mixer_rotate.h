#include <complex.h>

struct _mixer_rotate {
    complex double osc;
    complex double phase;
};

void mixer_init_rotate(struct _mixer_rotate *mixer_rotate, double freq, unsigned int samplerate);
void mixer_mix_rotate(complex float *sampleout, const complex float *samplein, struct _mixer_rotate *mixer_rotate, int samplelen);
