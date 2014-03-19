CC ?= gcc
CFLAGS ?= -Wall -O3
all:
	$(CC) $(CFLAGS) -g -o cas main.c atomic.c
	$(CC) $(CFLAGS) -c -S -o atomic.s atomic.c

clean:
	rm ./cas
	rm ./atomic.s
