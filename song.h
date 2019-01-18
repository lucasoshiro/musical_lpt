#ifndef _SONG
#define _SONG

#include "channel.h"

typedef struct {
    int      tempo;
    int      n_ch;
    channel *channels[1];
} song;

void song_print   (song *s);
void song_destroy (song *s);

#endif

