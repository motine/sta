# Find the meaning of the variables here: http://www.gnu.org/software/make/manual/make.html#Writing-Recipes-with-Directory-Search
CC=gcc
CFLAGS=-Ista -Wall -std=c11 $(shell sdl2-config --cflags)
LIBS=-lm -lSDL2_gfx -lSDL2_ttf $(shell sdl2-config --libs)

all: project

%.o: %.c %.h
	$(CC) -c -o $@ $< $(CFLAGS)

project: project.o sta/drawing.o sta/input.o sta/misc.o sta/sketchbook.o
	$(CC) -o $@ $^ $(CFLAGS) $(LIBS)

.SILENT:
.PHONY: clean
clean:
	rm -f *.o sta/*.o project
	rm -f shots/*.bmp
	
.PHONY: shots
shots: project
	gifsicle --version || ( echo "Please install gifsicle" && exit 1 )
	rm -f shots/*.bmp
	./project -s
	echo "combining shots (this can take a while)..."
	convert -delay 4 -loop 0 shots/*.bmp combined.gif # this needs image magick installed
	gifsicle -O3 --resize 400x300 --optimize=80 -o shots.gif combined.gif
	rm -f combined.gif
	# -- Optimization via ImageMagick (worse than gifsicle)
	# convert combined.gif -coalesce shots_tmp2.gif
	# convert -size 800x600 shots_tmp2.gif -resize 400x300 shots_tmp3.gif
	# convert shots_tmp3.gif +matte +map -layers optimize shots.gif
	# rm shots_tmp1.gif shots_tmp2.gif shots_tmp3.gif
	echo "result written to shots.gif"
	rm -f shots/*.bmp
