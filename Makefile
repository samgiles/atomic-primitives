CC ?= gcc
CFLAGS ?= -Wall -O3
all:
	$(CC) $(CFLAGS) -g -o cas main.c
	$(CC) $(CFLAGS) -c -S -o atomic.s main.c

clean:
	rm ./cas
	rm ./atomic.s
