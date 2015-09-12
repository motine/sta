CC=gcc
CFLAGS=-Ista -std=c99 $(shell sdl2-config --cflags)
LIBS=-lSDL2_gfx $(shell sdl2-config --libs)

all: project

%.o: %.c %.h
	$(CC) -c -o $@ $< $(CFLAGS)

project: project.o sta/drawing.o sta/misc.o sta/sketchbook.o
	gcc -o $@ $^ $(CFLAGS) $(LIBS)

.PHONY: clean
clean:
	rm -f *.o sta/*.o $(PROJECT)