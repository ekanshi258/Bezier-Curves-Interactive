CC = g++

DEPS := $(wildcard *.h)

CFLAGS := -Wall
LDFLAGS := -lGL -lGLU -lglut

.PHONY: all clean

all: bezier1.exe

bezier1.exe: bezier1.o
	$(CC) $^ -o $@ $(LDFLAGS)

bezier1.o: bezier1.cpp $(DEPS)
	$(CC) -c -o $@ $<

clean:
	$(RM)
