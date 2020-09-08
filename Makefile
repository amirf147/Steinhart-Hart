CC = gcc
CFLAGS = -Wall -Wextra -std=c11

default: steinhartHart

steinhartHart: steinhartHart.o calculateABC.o
	$(CC) $(CFLAGS) -o steinhartHart steinhartHart.o calculateABC.o -lm

steinhartHart.o: steinhartHart.c calculateABC.h
	$(CC) $(CFLAGS) -c steinhartHart.c

calculateABC.o: calculateABC.c calculateABC.h
	$(CC) $(CFLAGS) -c calculateABC.c

clean:
	$(RM) steinhartHart *.o *~                                   
