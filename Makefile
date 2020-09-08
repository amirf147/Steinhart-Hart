CC = gcc
CFLAGS = -Wall -Wextra -std=c11

default: steinhartHart

steinhartHart: steinhartHart.o ./calculations/calculateABC.o
	$(CC) $(CFLAGS) -o steinhartHart steinhartHart.o ./calculations/calculateABC.o -lm

steinhartHart.o: steinhartHart.c ./calculations/calculateABC.h
	$(CC) $(CFLAGS) -c steinhartHart.c

calculateABC.o: ./calculations/calculateABC.c ./calculations/calculateABC.h
	$(CC) $(CFLAGS) -c ./calculations/calculateABC.c

clean:
	$(RM) steinhartHart *.o *~ ./calculations/*.o ./calculations/*~                                 
