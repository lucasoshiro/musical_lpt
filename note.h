#ifndef _NOTE
#define _NOTE

typedef struct {
    int   silence;
    int   figure;               /* half-tones. 0 = C */
    int   octave;
    float duration;
} note;

void print_note (note n);

#endif

