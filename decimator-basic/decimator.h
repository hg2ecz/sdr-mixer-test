#include <string.h>
#include <complex.h>


#define MAXSAMPLESIZE 100000
#define MAXCOEFFLEN 256
#define MAXDECIM 100

typedef complex float osctype;

struct _mixer {
    osctype osc;
    osctype phase;
};

struct _decimstate {
    _Bool is_mix;
    struct _mixer mixer;       // if we need mixerfunc before decimate

    unsigned int decimfactor;
    unsigned int coefflen;
    float coeff_noncomplex[MAXCOEFFLEN]; // for ddc --> symmetric
//    complex float coeff[MAXCOEFFLEN];

    unsigned int samplelen;
    float complex sample[MAXSAMPLESIZE+MAXCOEFFLEN+MAXDECIM];
};

enum Window {
    Boxcar,
    Blackman,
    Hamming,
};


int decimator_init(struct _decimstate *ds, unsigned int mixfreq, unsigned int samplerate, unsigned int decimfactor,
                       float transition_bw, enum Window window);
int decimator(complex float *sampleout, const complex float *samplein, struct _decimstate *ds, int samplelen);
