#include <stdio.h>
#include <stdlib.h>
#include "parser.h"
#include "player.h"

int main (int ac, char *av[]) {
    song *s;
    if (ac < 2) exit(1);

    s = parse_file (av[1]);

    play_song (s);
    song_destroy (s);
    return 0;
}

