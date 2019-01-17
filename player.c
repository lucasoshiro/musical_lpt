#include "player.h"
#include <unistd.h>
#include <time.h>
#include <pthread.h>
#include <stdio.h>

static void  secsleep          (float ms);
static void  play_note         (note n,     int tempo);
static void  play_channel      (channel *c, int tempo);
static void *channel_thread_f  (void *args);

static void secsleep (float s) {
    struct timespec req;
    req.tv_sec  = s;
    req.tv_nsec = ((double) s - (double) req.tv_sec) * 1000000000;
    nanosleep (&req, NULL);
}

static void play_note (note n, int tempo) {
    float duration_s = n.duration / ((float) tempo / 60.);
    print_note (n);
    secsleep (duration_s);
}

static void play_channel (channel *c, int tempo) {
    for (note_cell *cell = c->first;
         cell != NULL;
         cell = cell->next) play_note (cell->n, tempo);
}

static void *channel_thread_f (void *arg) {
    struct {
        channel           *c;
        int                tempo;
        pthread_barrier_t *barrier;
    } *args = arg;

    pthread_barrier_wait ((args->barrier));
    play_channel (args->c, args->tempo);
    return NULL;
}

void play_song (song *s) {
    pthread_t         threads[32];
    pthread_barrier_t barrier;

    int n = s->n_ch;

    pthread_barrier_init (&barrier, NULL, s->n_ch);

    struct {
        channel           *c;
        int                tempo;
        pthread_barrier_t *barrier;
    } th_args[32];
        
    for (int i = 0; i < n; i++) {
        th_args[i].c       = s->channels[i];
        th_args[i].tempo   = s->tempo;
        th_args[i].barrier = &barrier;

        pthread_create (threads + i, NULL,
                        channel_thread_f,
                        (void *) (th_args + i));
    }
    
    for (int i = 0; i < n; i++) pthread_join (threads[i], NULL);
}
