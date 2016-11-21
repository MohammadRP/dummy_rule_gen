CC=gcc
CFLAGS=-I.

all:
	$(CC) -o dummy_rule_gen main.c -I.
	
	
clean:
	rm -rf *.o
