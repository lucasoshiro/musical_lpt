#include "player.h"
#include <unistd.h>

static void play_note    (note *n,    int tempo);
static void play_channel (channel *s, int tempo);

static void play_note (note *n, int tempo) {
    float duration_s = n->duration * ((float) tempo / 60.);
}

void play_song (song *s) {
    
}
