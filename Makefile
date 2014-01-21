

CC=gcc
CFLAGS= -g -O3 -Wall
LFLAGS= -lrt -lm

BUILD = $(CC) $(CFLAGS)

sort: sort.c sort.h
	$(BUILD) sort.c -o sort $(LFLAGS)

clean:
	rm sort;
	rm *.o;


