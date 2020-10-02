# Makefile to build minimum binary to bootstrap ltd.

CC=g++
INCLUDE=./inc
TARGET=./
CFLAGS=-I$(INCLUDE) -std=c++17
LIBS=-lstdc++fs

_DEPS=application.h buffers.h containers.h datetime.h errors.h fmt.h ltd.h memory.h ptr.h stdalias.h testunit.h 
DEPS = $(patsubst %,$(INCLUDE)/%,$(_DEPS))

_OBJ_LIB=allocators.o application.o datetime.o errors.o fmt.o memory.o testunit.o 
OBJ_LIB=$(patsubst %.o, bin/lib/%.o, $(_OBJ_LIB))

bin/lib/%.o: lib/%.cpp $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

bin/tests/%.o: tests/%.cpp $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

bin/demos/%.o: demos/%.cpp $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

bin/tests/%: bin/tests/%.o $(OBJ_LIB) bin/lib/main.o 
	$(CC) -o $@ $^ $(CFLAGS) $(LIBS) 

tests: bin/tests/tests bin/tests/ptr bin/tests/returns bin/tests/arrays
	bin/tests/tests
	bin/tests/ptr
	bin/tests/returns
	bin/tests/arrays

sandbox: bin/demos/sandbox.o $(OBJ_LIB)
	$(CC) -o bin/demos/sandbox $^ $(CFLAGS) $(LIBS) 

all: tests 