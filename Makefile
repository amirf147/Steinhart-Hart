CC = gcc
CFLAGS = -Wall -Wextra -std=c11

default: steinhartHart

steinhartHart: steinhartHart.o ./Calculations/calculateABC.o
	$(CC) $(CFLAGS) -o steinhartHart steinhartHart.o ./Calculations/calculateABC.o -lm

steinhartHart.o: steinhartHart.c ./Calculations/calculateABC.h
	$(CC) $(CFLAGS) -c steinhartHart.c

calculateABC.o: ./Calculations/calculateABC.c ./Calculations/calculateABC.h
	$(CC) $(CFLAGS) -c ./Calculations/calculateABC.c

clean:
	$(RM) steinhartHart *.o *~ ./Calculations/*.o ./Calculations/*~                                 
