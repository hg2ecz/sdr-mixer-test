#if defined(__arm__) || defined(__aarch64__)
  #include <arm_neon.h>
  typedef float32x4_t VECTYPE;
#elif defined (__SSE__)
  #include <smmintrin.h>
  typedef __v4sf VECTYPE;
#endif

struct _sample {
    float re[4*SAMPLELEN4];
    float im[4*SAMPLELEN4];
};

struct _mixer_rotate_float_vec {
    VECTYPE osc_re;
    VECTYPE osc_im;
    VECTYPE phase_re;
    VECTYPE phase_im;
};

void mixer_init_rotate_float_vec(struct _mixer_rotate_float_vec *mixer_rotate_float, double freq, unsigned int samplerate);
void mixer_mix_rotate_float_vec(struct _sample *sampleout, const struct _sample *samplein, struct _mixer_rotate_float_vec *mixer_rotate_float);
