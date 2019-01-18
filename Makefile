CFLAGS = -Wall -pedantic -O2
CLIBS = -lpthread -lm

.PHONY: all
all: mp

mp: mp.c parser.o channel.o song.o note.o player.o tone.o
	gcc $(CFLAGS) $^ -o $@ $(CLIBS) -g

%.o: %.c 
	gcc $(CFLAGS) $^ -c -o $@ -g

.PHONY: clean
clean:
	rm -f mp *.o

