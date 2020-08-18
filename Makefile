# Makefile to build minimum binary to bootstrap ltd.

CC=g++
INCLUDE=./inc
TARGET=./
CFLAGS=-I$(INCLUDE) -std=c++17 -Wall -pedantic
LIBS=-lstdc++fs

_DEPS=application.h errors.h ltd.h testunit.h
DEPS = $(patsubst %,$(INCLUDE)/%,$(_DEPS))

_OBJ_LIB=application.o errors.o main.o testunit.o
OBJ_LIB=$(patsubst %.o, bin/lib/%.o, $(_OBJ_LIB))

bin/lib/%.o: lib/%.cpp $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

01_test:

test: 01_test

all: $(OBJ_LIB)
