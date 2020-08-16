# Makefile to build minimum binary to bootstrap ltd.

CC=g++
INCLUDE=./inc
TARGET=./
CFLAGS=-I$(INCLUDE) -std=c++17 -Wall -pedantic
LIBS=-lstdc++fs



