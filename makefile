CC=gcc
CFLAGS=-I.

all:
	$(CC) -o main.o main.c -I.
	
	
clean:
	rm -rf *.o
