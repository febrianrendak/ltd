# Makefile to build minimum binary to bootstrap ltd.

CC=g++
INCLUDE=./inc
TARGET=./
CFLAGS=-I$(INCLUDE) -std=c++17 -Wall -pedantic
LIBS=-lstdc++fs

_DEPS=application.h errors.h fmt.h ltd.h testunit.h datetime.h
DEPS = $(patsubst %,$(INCLUDE)/%,$(_DEPS))

_OBJ_LIB=application.o errors.o fmt.o main.o testunit.o datetime.o
OBJ_LIB=$(patsubst %.o, bin/lib/%.o, $(_OBJ_LIB))

bin/lib/%.o: lib/%.cpp $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

bin/tests/%.o: tests/%.cpp $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

bin/%test: bin/tests/%test.o $(OBJ_LIB)
	$(CC) -o $@ $^ $(CFLAGS) $(LIBS)

tests: bin/01_test

all: tests