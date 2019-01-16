#include "song.h"
#include "note.h"
#include <stdio.h>
#include <stdlib.h>

void song_print (song *s) {
    printf ("TEMPO = %d, CHANNELS = %d\n\n", s->tempo, s->n_ch);

    for (int i = 0; i < s->n_ch; i++) {
        printf ("CHANNEL %d:\n", i);

        for (note_cell *cell = s->channels[i]->first;
             cell != NULL;
             cell = cell->next) print_note (cell->n);

    }
}

void song_destroy (song *s) {
    for (int i = 0; i < s->n_ch; i++) channel_destroy (s->channels[i]);
    free (s);
}

