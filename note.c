#include "note.h"
#include <stdio.h>

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

void print_note (note n) {
    char buffer[3];

    *buffer = '\0';
    unparse_figure (buffer, n.figure);
            
    printf ("NOTE: %s%c %5.2f\n",
            n.silence ? "-" : buffer,
            n.silence ? ' ' : '0' + n.octave,
            n.duration);
    
}

