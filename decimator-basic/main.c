#include <time.h>
#include <stdio.h>

#include "decimator.h"

#define ITERATION 1000

int main() {
    double eltime;
    struct timespec gstart, gend;

    complex float samplein[MAXSAMPLESIZE];
    complex float sampleout[MAXSAMPLESIZE];
    struct _decimstate decimstate;

    int sumsamplein = 0;
    int sumsampleout = 0;

    decimator_init(&decimstate, 300000, 2400*1000, 10, 0.051, Hamming);

    clock_gettime(CLOCK_PROCESS_CPUTIME_ID, &gstart); // start time
    for (int i=0; i<ITERATION; i++) {
        int outlen = decimator(sampleout, samplein, &decimstate, MAXSAMPLESIZE);
        sumsamplein += MAXSAMPLESIZE;
        sumsampleout += outlen;
    }
    clock_gettime(CLOCK_PROCESS_CPUTIME_ID, &gend);   // end time
    eltime = gend.tv_sec - gstart.tv_sec + (gend.tv_nsec - gstart.tv_nsec)/(1000.*1000.*1000.);
    printf("Decimator(10) inspeed: %.1f Msps\n", (double)sumsamplein/(1000.*1000.)/eltime);
    printf("Decimator(10) outspeed: %.1f Msps\n", (double)sumsampleout/(1000.*1000.)/eltime);
}
