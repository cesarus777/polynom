CC=g++
CFLAGS=-c -Wall -Wextra

all: main.cpp main

main: main.o

.PHONY: test

test: main test.txt
	./main < test.txt

.PHONY: clean

clean:
	rm -rf *.o

