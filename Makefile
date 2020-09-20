CC = gcc
CFLAGS = -Wall -Wextra -std=c11

default: steinhartHart

steinhartHart: steinhartHart.o ./calculations/calculateABC.o ./calculations/adcToResist.o
	$(CC) $(CFLAGS) -o steinhartHart steinhartHart.o ./calculations/adcToResist.o ./calculations/calculateABC.o ./calculations/sHformula.o -lm

steinhartHart.o: steinhartHart.c ./calculations/calculateABC.h ./calculations/adcToResist.h ./calculations/sHformula.o

	$(CC) $(CFLAGS) -c steinhartHart.c

calculateABC.o: ./calculations/calculateABC.c ./calculations/calculateABC.h

	$(CC) $(CFLAGS) -c ./calculations/calculateABC.c

adcToResist.o: ./calculations/adcToResist.c ./calculations/adcToResist.h

	$(CC) $(CFLAGS) -c ./calculations/adcToResist.c

sHformula.o: ./calculations/sHformula.c ./calculations/sHformula.h

	$(CC) $(CFLAGS) -c ./calculations/sHformula.c

clean:
	$(RM) steinhartHart *.o *~ ./calculations/*.o ./calculations/*~                              
