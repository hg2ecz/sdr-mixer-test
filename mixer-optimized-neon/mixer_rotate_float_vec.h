#include "vec_types.h"

struct _mixer_rotate_float_vec {
    VECTYPE osc_re;
    VECTYPE osc_im;
    VECTYPE phase_re;
    VECTYPE phase_im;
};

void mixer_init_rotate_float_vec(struct _mixer_rotate_float_vec *mixer_rotate_float, double freq, unsigned int samplerate);
void mixer_mix_rotate_float_vec(struct _sample *sampleout, const struct _sample *samplein, struct _mixer_rotate_float_vec *mixer_rotate_float);
