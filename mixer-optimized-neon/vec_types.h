#if defined(__arm__) || defined(__aarch64__)
  #include <arm_neon.h>
  typedef float32x4_t VECTYPE;
#elif defined (__SSE__)
  #include <smmintrin.h>
  typedef __v4sf VECTYPE;
#endif

#ifndef _SAMPLE_
#  define _SAMPLE_
struct _sample {
    float re[4*SAMPLELEN4];
    float im[4*SAMPLELEN4];
};
#endif
