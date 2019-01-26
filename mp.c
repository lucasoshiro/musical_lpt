#include <stdlib.h>
#include "parser.h"
#include "player.h"

char *file_path;

void parse_arguments (int ac, char *av[]) {
    if (ac < 2) exit(1);

    for (int i = 1; i < ac; i++) {
	if (av[i][0] == '-') {
	    switch (av[i][1]) {
	    case 's': silent  = 1; break;
	    case 'v': verbose = 1; break;
	    }
	}
	else {
	    file_path = av[i];
	}
    }
}

int main (int ac, char *av[]) {
    song *s;
    parse_arguments (ac, av);
    s = parse_file (file_path);
    play_song (s);
    song_destroy (s);
    return 0;
}

