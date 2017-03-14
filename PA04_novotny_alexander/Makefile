PROGRAM_NAME=sort
CFLAGS=-c -Wall -std=c++11

# By defult, run unit testing after compiling
all: sort

# Main program for assignment
sort: PA04.o QuickSort.o InsertionSort.o CountingSort.o Sort.o
	g++ PA04.o QuickSort.o InsertionSort.o CountingSort.o Sort.o -o $(PROGRAM_NAME)

%.o: %.cpp
	g++ $(CFLAGS) $<

clean:
	rm *.o