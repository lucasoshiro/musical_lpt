#ifndef _NOTE
#define _NOTE

typedef struct {
    int   silence;
    int   figure;
    int   octave;
    float duration;
} note;

void print_note (note n);

#endif
