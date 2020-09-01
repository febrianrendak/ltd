# Makefile to build minimum binary to bootstrap ltd.

CC=g++
INCLUDE=./inc
TARGET=./
CFLAGS=-I$(INCLUDE) -std=c++17 -Wall -pedantic
LIBS=-lstdc++fs

_DEPS=application.h errors.h fmt.h ltd.h testunit.h datetime.h
DEPS = $(patsubst %,$(INCLUDE)/%,$(_DEPS))

_OBJ_LIB=application.o datetime.o errors.o fmt.o main.o testunit.o 
OBJ_LIB=$(patsubst %.o, bin/lib/%.o, $(_OBJ_LIB))

bin/lib/%.o: lib/%.cpp $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

bin/tests/%.o: tests/%.cpp $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

bin/tests/%: bin/tests/%.o $(OBJ_LIB)
	$(CC) -o $@ $^ $(CFLAGS) $(LIBS)

tests: bin/tests/01_test bin/tests/02_ptr bin/tests/03_returns bin/tests/04_arrays
	bin/tests/01_test
	bin/tests/02_ptr
	bin/tests/03_returns
	bin/tests/04_arrays

all: tests