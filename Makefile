# Find the meaning of the variables here: http://www.gnu.org/software/make/manual/make.html#Writing-Recipes-with-Directory-Search
CC=gcc
CFLAGS=-Ista -fdiagnostics-color=always -Wall -std=c11 $(shell sdl2-config --cflags)
LIBS=-lm -lSDL2_gfx -lSDL2_ttf $(shell sdl2-config --libs)

all: project

%.o: %.c %.h
	$(CC) -c -o $@ $< $(CFLAGS)

project: project.o sta/drawing.o sta/input.o sta/misc.o sta/sketchbook.o
	$(CC) -o $@ $^ $(CFLAGS) $(LIBS)

.SILENT:
.PHONY: clean
clean:
	rm -f *.o sta/*.o $(PROJECT)
	
.PHONY: shots
shots: project
	rm -f shots/*.bmp
	./project -s
	./make_gif.sh
	rm -f shots/*.bmp
