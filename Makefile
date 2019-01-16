CFLAGS = -Wall -pedantic -O3

.PHONY: all
all: mp

mp: mp.c parser.o channel.o song.o note.o player.o
	gcc $(CFLAGS) $^ -o $@ -lpthread -g

%.o: %.c 
	gcc $(CFLAGS) $^ -c -o $@ -lpthread -g

.PHONY: clean
clean:
	rm -f mp *.o
