#include "player.h"
#include <unistd.h>
#include <time.h>

static void secsleep     (float ms);
static void play_note    (note n,     int tempo);
static void play_channel (channel *s, int tempo);

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

static void play_channel (channel *s, int tempo) {
    for (note_cell *cell = s->first;
         cell != NULL;
         cell = cell->next) play_note (cell->n, tempo);
}

void play_song (song *s) {
    play_channel (s->channels[0], s->tempo);
}
