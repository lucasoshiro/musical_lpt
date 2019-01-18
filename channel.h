#ifndef _CHANNEL
#define _CHANNEL

#include "note.h"

typedef struct note_cell {
    note n;
    struct note_cell *next;
} note_cell;

typedef struct {
    note_cell *first;
    note_cell *last;
} channel;

channel *channel_new     ();
void     channel_destroy (channel *ch);
void     insert_note     (channel *ch, note n);

#endif

