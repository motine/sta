CC=gcc
CFLAGS=-Iinclude -std=c99 $(shell sdl2-config --cflags)
LIBS=-lSDL2_gfx $(shell sdl2-config --libs)
PROJECT?= default # if there is no environment variable present

all: $(PROJECT)

%.o: %.c # add %.h
	$(CC) -c -o $@ $< $(CFLAGS)

$(PROJECT): $(PROJECT:=.o)
	gcc -o $@ $^ $(CFLAGS) $(LIBS)

.PHONY: clean
clean:
	rm -f *.o $(PROJECT)