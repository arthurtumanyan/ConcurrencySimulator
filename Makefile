CC = g++
CFLAGS  = -Wall -Wextra -std=c++11

default: cs

cs:  main.o ConcurrencySimulator.o 
	$(CC) $(CFLAGS) -o cs ConcurrencySimulator.o main.o

#
main.o:  main.cpp 
	$(CC) $(CFLAGS) -c main.cpp

#
ConcurrencySimulator.o:  ConcurrencySimulator.cpp 
	$(CC) $(CFLAGS) -c ConcurrencySimulator.cpp

#
clean: 
	$(RM) cs *.o *~
