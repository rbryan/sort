

CC=gcc
CFLAGS= -g -O3 -Wall
LFLAGS=

BUILD = $(CC) $(CFLAGS)

sort: sort.c sort.h
	$(BUILD) sort.c -o sort

clean:
	rm *.o;
	rm sort;


