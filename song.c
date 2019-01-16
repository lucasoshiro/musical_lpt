#include "song.h"
#include <stdio.h>
#include <stdlib.h>

static void unparse_figure (char *s, int figure);

static void unparse_figure (char *s, int figure) {
    char conv[2][13] = {
        "CCDDEFFGGAAB",
        "\0#\0#\0\0#\0#\0#\0"
    };

    s[0] = conv[0][figure];
    s[1] = conv[1][figure];
    s[2] = '\0';
}

void song_print (song *s) {
    printf ("TEMPO = %d, CHANNELS = %d\n\n", s->tempo, s->n_ch);

    for (int i = 0; i < s->n_ch; i++) {
        printf ("CHANNEL %d:\n", i);

        for (note_cell *cell = s->channels[i]->first;
             cell != NULL;
             cell = cell->next) {

            char buffer[3];
            note n = cell->n;

            *buffer = '\0';

            unparse_figure (buffer, n.figure);
            
            printf ("NOTE: %s%c %5.2f\n",
                    n.silence ? "-" : buffer,
                    n.silence ? ' ' : '0' + n.octave,
                    n.duration);
        }
    }
}

void song_destroy (song *s) {
    for (int i = 0; i < s->n_ch; i++) channel_destroy (s->channels[i]);
    free (s);
}

