CC=gcc
CFLAGS=-Idrawing -std=c99 $(shell sdl2-config --cflags)
LIBS=-lSDL2_gfx $(shell sdl2-config --libs)
PROJECT?=default # we set the project name to 'default' if there is no environment variable present

all: $(PROJECT)

%.o: %.c %.h
	$(CC) -c -o $@ $< $(CFLAGS)

$(PROJECT): $(PROJECT:=.o) drawing/drawing.o drawing/misc.o drawing/sketchbook.o
	gcc -o $@ $^ $(CFLAGS) $(LIBS)

.PHONY: clean
clean:
	rm -f *.o drawing/*.o $(PROJECT)