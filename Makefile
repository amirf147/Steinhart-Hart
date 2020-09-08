CC = gcc
CFLAGS = -Wall -Wextra -std=c11

default: steinhartHart

steinhartHart: steinhartHart.o ./calculations/calculateABC.o ./calculations/adcToResist.o
	$(CC) $(CFLAGS) -o steinhartHart steinhartHart.o ./calculations/adcToResist.o ./calculations/calculateABC.o -lm

steinhartHart.o: steinhartHart.c ./calculations/calculateABC.h ./calculations/adcToResist.h
	$(CC) $(CFLAGS) -c steinhartHart.c

calculateABC.o: ./calculations/calculateABC.c ./calculations/calculateABC.h
	$(CC) $(CFLAGS) -c ./calculations/calculateABC.c

adcToResist.o: ./calculations/adcToResist.c ./calculations/adcToResist.h

clean:
	$(RM) steinhartHart *.o *~ ./calculations/*.o ./calculations/*~                                 
