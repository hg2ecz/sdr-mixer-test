#include <time.h>
#include <stdio.h>

#ifdef FLOATVECBENCH
#  include "mixer_rotate_float_vec.h"
#endif

#include "mixer_rotate_float.h"
#include "mixer_rotate.h"
#include "mixer_table.h"

//#define freq 100111
#define freq 100000
#define samplerate 2400000

int main() {
    double eltime;
    struct timespec gstart, gend;

    complex float samplein[4*SAMPLELEN4];
    complex float sampleout[4*SAMPLELEN4];
    struct _mixer_rotate_float mixer_rotate_float;
    struct _mixer_rotate mixer_rotate;
    struct _mixer_table  mixer_table;

    mixer_init_rotate_float(&mixer_rotate_float, freq, samplerate);
    mixer_init_rotate(&mixer_rotate, freq, samplerate);
    mixer_init_table (&mixer_table,  freq, samplerate);

#ifdef FLOATVECBENCH
    // rotate float vec bench
    struct _sample sampleblockin;
    struct _sample sampleblockout;
    struct _mixer_rotate_float_vec mixer_rotate_float_vec;
    mixer_init_rotate_float_vec(&mixer_rotate_float_vec, freq, samplerate);

    clock_gettime(CLOCK_PROCESS_CPUTIME_ID, &gstart); // start time
    for (int i=0; i<ITERATION; i++) {
        mixer_mix_rotate_float_vec(&sampleblockout, &sampleblockin, &mixer_rotate_float_vec);
    }
    clock_gettime(CLOCK_PROCESS_CPUTIME_ID, &gend);   // end time
    eltime = gend.tv_sec - gstart.tv_sec + (gend.tv_nsec - gstart.tv_nsec)/(1000.*1000.*1000.);
    printf("\nMixer_rotate_float_vec speed: %.1f Msps\n", (double)ITERATION*4*SAMPLELEN4/(1000.*1000.)/eltime);
#endif

    // rotate float bench
    clock_gettime(CLOCK_PROCESS_CPUTIME_ID, &gstart); // start time
    for (int i=0; i<ITERATION; i++) {
        mixer_mix_rotate_float(sampleout, samplein, &mixer_rotate_float, SAMPLELEN4);
    }
    clock_gettime(CLOCK_PROCESS_CPUTIME_ID, &gend);   // end time
    eltime = gend.tv_sec - gstart.tv_sec + (gend.tv_nsec - gstart.tv_nsec)/(1000.*1000.*1000.);
    printf("\nMixer_rotate_float speed: %.1f Msps\n", (double)ITERATION*4*SAMPLELEN4/(1000.*1000.)/eltime);

    printf("%.1f million step, float abs(osc): %.16f\n\n", (double)ITERATION*4*SAMPLELEN4/(1000.*1000.), cabs(mixer_rotate_float.osc));

    // rotate double bench
    clock_gettime(CLOCK_PROCESS_CPUTIME_ID, &gstart); // start time
    for (int i=0; i<ITERATION; i++) {
        mixer_mix_rotate(sampleout, samplein, &mixer_rotate, SAMPLELEN4);
    }
    clock_gettime(CLOCK_PROCESS_CPUTIME_ID, &gend);   // end time
    eltime = gend.tv_sec - gstart.tv_sec + (gend.tv_nsec - gstart.tv_nsec)/(1000.*1000.*1000.);
    printf("\nMixer_rotate speed: %.1f Msps\n", (double)ITERATION*4*SAMPLELEN4/(1000.*1000.)/eltime);

    printf("%.1f million step, abs(osc): %.16f\n\n", (double)ITERATION*4*SAMPLELEN4/(1000.*1000.), cabs(mixer_rotate.osc));

    // table bench
    clock_gettime(CLOCK_PROCESS_CPUTIME_ID, &gstart); // start time
    for (int i=0; i<ITERATION; i++) {
        mixer_mix_table(sampleout, samplein, &mixer_table, SAMPLELEN4);
    }
    clock_gettime(CLOCK_PROCESS_CPUTIME_ID, &gend);   // end time
    eltime = gend.tv_sec - gstart.tv_sec + (gend.tv_nsec - gstart.tv_nsec)/(1000.*1000.*1000.);
    printf("\nMixer_table  speed: %.1f Msps\n", (double)ITERATION*4*SAMPLELEN4/(1000.*1000.)/eltime);
}
