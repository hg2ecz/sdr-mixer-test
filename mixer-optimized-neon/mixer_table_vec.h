#include "vec_types.h"

#define MAXMIXTABLE (4*100)
struct _mixer_table_vec {
    int len4;
    int actpos4;
    VECTYPE mix_re[MAXMIXTABLE];
    VECTYPE mix_im[MAXMIXTABLE];
};

void mixer_init_table_vec(struct _mixer_table_vec *mixer_table_vec, double freq, unsigned int samplerate);
void mixer_mix_table_vec(struct _sample *sampleout, const struct _sample *samplein, struct _mixer_table_vec *mixer_table_vec);
