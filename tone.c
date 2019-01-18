#include "tone.h"

#include <stdio.h>
#include <stdlib.h>
#include <sys/io.h>
#include <time.h>

#define BASE 0x378

#define set_lpt_val(val) (outb (val, BASE))

unsigned char state = 0;

void lpt_init () {
    if (ioperm (BASE, 8, 1)) fprintf (stderr, "Access denied\n"), exit (1);
}

void tone (int freq, double duration) {
    unsigned char state = 0;
    double start;
    long period = 1000000000 / freq;

    struct timespec delay = {0, period / 2};

    start = (double) clock () / CLOCKS_PER_SEC;

    while (((double) clock () / CLOCKS_PER_SEC - start) < duration) {
        set_lpt_val (state ^= 1);
        nanosleep (&delay, NULL);
        set_lpt_val (state ^= 1);
        nanosleep (&delay, NULL);
    }
}

