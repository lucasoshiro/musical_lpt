#include "parser.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define EQ(s1, s2) (strcmp (s1, s2) == 0)

static int   parse_figure (char *s);
static note *parse_note   (char *s);

static int parse_figure (char *s) {
    const int conv[] = {0, 2, 4, 5, 7, 9, 11};
    int base = conv[(s[0] - 'A' + 12) % 7];

    switch (s[1]) {
    case '#': return base + 1;
    case 'b': return base - 1;
    default:  return base;
    }
}

static note *parse_note (char *s) {
    note *n;
    char bff[3];
    *bff = '\0';

    n = malloc (sizeof *n);
    n->figure = 0, n->octave = 9, n->silence = (s[0] == '-');

    if (n->silence) {
        int retval = sscanf (s+1, "%f", &n->duration);
        if (retval != 1) return NULL;
        return n;
    }

    int retval = sscanf (s, "%s%d%f",
                         bff,
                         &n->octave,
                         &n->duration);

    if ((retval != 3) ||
        ((bff[0] < 'A' || bff[0] > 'G') && (bff[0] != '-')) ||
        (bff[1] != '\0' && bff[1] != '#' && bff[1] != 'b') ||
        (n->octave > 8)) {
        free (n);
        return NULL;
    }
    
    n->figure = n->silence ? 0: parse_figure (bff);
    return n;
}

static int next_line (FILE *f, char *buffer) {
    char *c;
    int ret;

    for (c = buffer;
         *c = getc (f), (*c != '\n' && *c != '\r' && *c != EOF);
         c++);

    ret = *c;
    
    *c = '\0';
    return ret;
}

song *parse_file (char *path) {
    char     buffer[64];
    channel *chs[32];

    FILE *f = fopen (path, "r");
    song *s = NULL;

    int tempo = 0, n_ch = 0;
    int in_ch = 0;

    channel **ch = chs;

    while (next_line (f, buffer) != EOF) {
        char cmm[32];
        int  p;

        if (buffer[0] == '%') continue;

        *cmm = '\0';
        (void) sscanf (buffer, "%s %d", cmm, &p);

        if      (EQ (cmm, "BEGINCH"))  in_ch  = 1, ch = chs+p, *ch = channel_new ();
        else if (EQ (cmm, "ENDCH"))    in_ch  = 0;
        else if (EQ (cmm, "TEMPO"))    tempo  = p;
        else if (EQ (cmm, "CHANNELS")) n_ch   = p;
        else if (in_ch) {
            note *n = parse_note (buffer);
            if (n == NULL) continue;

            insert_note (*ch, *n);

            free (n);
            continue;
        }
    }
    
    fclose (f);

    if (tempo > 0 && n_ch > 0) {
        s = malloc (sizeof *s + (n_ch - 1) * sizeof (channel *));
        s->n_ch  = n_ch;
        s->tempo = tempo;
        memcpy(s->channels, chs, n_ch * sizeof (channel *));
    }

    return s;
}

