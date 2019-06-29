#include <math.h>
#include "mixer_rotate_float_vec.h"

void mixer_init_rotate_float_vec(struct _mixer_rotate_float_vec *mixer_rotate_float, double freq, unsigned int samplerate) {
    double phase_radian = 2*M_PI*freq/samplerate;
    mixer_rotate_float->osc_re[0] = 1. + 0.j;
    mixer_rotate_float->osc_re[1] = cos(1*phase_radian);
    mixer_rotate_float->osc_re[2] = cos(2*phase_radian);
    mixer_rotate_float->osc_re[3] = cos(3*phase_radian);

    mixer_rotate_float->osc_im[0] = 0.;
    mixer_rotate_float->osc_im[1] = sin(1*phase_radian);
    mixer_rotate_float->osc_im[2] = sin(2*phase_radian);
    mixer_rotate_float->osc_im[3] = sin(3*phase_radian);

    mixer_rotate_float->phase_re[0] = cos(4*phase_radian);
    mixer_rotate_float->phase_re[1] = cos(4*phase_radian);
    mixer_rotate_float->phase_re[2] = cos(4*phase_radian);
    mixer_rotate_float->phase_re[3] = cos(4*phase_radian);

    mixer_rotate_float->phase_im[0] = sin(4*phase_radian);
    mixer_rotate_float->phase_im[1] = sin(4*phase_radian);
    mixer_rotate_float->phase_im[2] = sin(4*phase_radian);
    mixer_rotate_float->phase_im[3] = sin(4*phase_radian);
}

void mixer_mix_rotate_float_vec(struct _sample *sampleout, const struct _sample *samplein, struct _mixer_rotate_float_vec *mixer_rotate_float) {
    VECTYPE osc_re = mixer_rotate_float->osc_re;      // register -> faster
    VECTYPE osc_im = mixer_rotate_float->osc_im;
    VECTYPE phase_re = mixer_rotate_float->phase_re;  // register -> faster
    VECTYPE phase_im = mixer_rotate_float->phase_im;

    for (int i=0; i<4*SAMPLELEN4; i+=4) {
        VECTYPE s_in_re = *((VECTYPE *)&samplein->re[i]);
        VECTYPE s_in_im = *((VECTYPE *)&samplein->im[i]);

        VECTYPE *s_out_re = (VECTYPE *)&sampleout->re[i];
        VECTYPE *s_out_im = (VECTYPE *)&sampleout->im[i];

        *s_out_re = s_in_re * osc_re - s_in_im * osc_im;
        *s_out_im = s_in_re * osc_im + s_in_im * osc_re;

        VECTYPE osc_re_tmp = osc_re;
        osc_re = osc_re_tmp * phase_re - osc_im * phase_im;
        osc_im = osc_re_tmp * phase_im + osc_im * phase_re;
    }

    mixer_rotate_float->osc_re = osc_re;                       // store back from register
    mixer_rotate_float->osc_im = osc_im;                       // store back from register
}
