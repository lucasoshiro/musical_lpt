#include "channel.h"
#include <stdlib.h>

static void list_destroy (note_cell *l);

static void list_destroy (note_cell *l) {
    if (l == NULL) return;
    list_destroy (l->next);
    free (l);
}

channel *channel_new () {
    channel *ch = malloc (sizeof *ch);
    ch->first = ch->last = NULL;
    return ch;
}

void channel_destroy (channel *ch) {
    list_destroy (ch->first);
    free (ch);
}

void insert_note (channel *ch, note n) {
    note_cell *cell = malloc (sizeof *cell);
    cell->n = n;
    cell->next = NULL;

    if (ch->first == NULL)
        ch->first = cell;
    else
        ch->last->next = cell;
    ch->last = cell;
}

