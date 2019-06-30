#include <complex.h>

#define MAXMIXTABLE (4*100)
struct _mixer_table {
    int len;
    int actpos;
    complex float mix[MAXMIXTABLE];
};

void mixer_init_table(struct _mixer_table *mixer_table, double freq, unsigned int samplerate);
void mixer_mix_table(complex float *sampleout, const complex float *samplein, struct _mixer_table *mixer_table, int samplelen4);
