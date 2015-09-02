
for reference: open /usr/local/Cellar/sdl2_gfx/1.0.0/include/

TODO
vagrant: create ubuntu with desktop (folder shall include all C code)
on mac: i installed `brew install sdl2 sdl2_gfx`

create a console command:

- keeps a number of templates under `~/.sta/templates/*`
- new: create a new folder with template inside, c file (and header).
- update: download new templates and headers/c files from github
- compile: ?

write a wrapper which can:

- set the color for stroke and fill
- draw ellipses, rects, lines (filled and outlines, mind the previously set color)
- have a random() and millis() function
- have two modes
 - static: no loop, but a wait at the end
 - dynamic: has a loop() method and can react to key strokes etc.
- have key and mouse handling (variables can be queried by the loop)
