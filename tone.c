#include "tone.h"

#include <stdio.h>
#include <stdlib.h>
#include <sys/io.h>
#include <time.h>
#include <pthread.h>

#define BASE 0x378

#define set_lpt_val(val) (outb (val, BASE))

unsigned char state = 0;

static void *tone_thread_f (void *arg) {
    unsigned char state = 0;
        struct {
        struct timespec freq_delay;
        parallel_pin pin;
        } *args = arg;

    for (;;) {
        set_lpt_val (state ^= args->pin); nanosleep (&(args->freq_delay), NULL);
        set_lpt_val (state ^= args->pin); nanosleep (&(args->freq_delay), NULL);
    }
    return NULL;
}

void lpt_init () {
    if (ioperm (BASE, 8, 1)) fprintf (stderr, "Access denied\n"), exit (1);
}

void tone (int freq, double duration, parallel_pin pin) {
    long half_period = 500000000 / freq;
    pthread_t tone_thread;

    struct timespec freq_delay;
    freq_delay.tv_sec = 0;
    freq_delay.tv_nsec = half_period;

    struct timespec  tempo_delay;
    tempo_delay.tv_sec = (int) duration;
    tempo_delay.tv_nsec = (duration - tempo_delay.tv_sec) * 1e9;

    struct {
        struct timespec freq_delay;
        parallel_pin pin;
    } *arg = malloc (sizeof *arg);

    arg->freq_delay = freq_delay;
    arg->pin = pin;

    pthread_create (&tone_thread, NULL, tone_thread_f, arg);

    nanosleep (&tempo_delay, NULL);

    pthread_cancel (tone_thread);

    free (arg);
}

