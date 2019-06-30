#include <string.h>

#if defined(__arm__) || defined(__aarch64__)
  #include <arm_neon.h>
  typedef float32x4_t VECTYPE;
#elif defined (__SSE__)
  #include <smmintrin.h>
  typedef __v4sf VECTYPE;
#endif

#define MAXSAMPLESIZE 100000
#define MAXCOEFFLEN 256
#define MAXDECIM 100

struct _sample {
    unsigned int len;
    float re[MAXSAMPLESIZE];
    float im[MAXSAMPLESIZE];
};

struct _mixer {
    VECTYPE osc_re;
    VECTYPE osc_im;
    VECTYPE phase_re;
    VECTYPE phase_im;
};

struct _decimstate {
    _Bool is_mix;
    struct _mixer mixer;       // if we need mixerfunc before decimate

    unsigned int decimfactor;
    unsigned int coefflen4;
    VECTYPE coeff_noncomplex[MAXCOEFFLEN/4]; // for ddc --> symmetric
//    VECTYPE coeff_re[MAXCOEFFLEN/4];
//    VECTYPE coeff_im[MAXCOEFFLEN/4];

    unsigned int samplelen;
    float sample_re[MAXSAMPLESIZE+MAXCOEFFLEN+MAXDECIM];
    float sample_im[MAXSAMPLESIZE+MAXCOEFFLEN+MAXDECIM];
};

enum Window {
    Boxcar,
    Blackman,
    Hamming,
};


int fastdecimator_init(struct _decimstate *ds, unsigned int mixfreq, unsigned int samplerate, unsigned int decimfactor,
                       float transition_bw, enum Window window);
int fastdecimator(struct _sample *sampleout, const struct _sample *samplein, struct _decimstate *ds);
