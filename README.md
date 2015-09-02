# Simple Teaching Assistant

**This is not ripe yet. I will add more documentation as soon as I get somewhere with this project.**

The Simple Teaching Assistant helps in bringing programming to students.
Since our students will become engineers, we chose `C` as a language.
But there is an allure to projects like [Processing](https://processing.org/), which teach programming a little more visual.

The Simple Teaching Assistant takes the edge off of graphical programming by providing a ready-made environment.
The `sta` tool lets the student easily create projects and compile them.
These (new) projects are derived from a template. 
The default template offers a set of simple drawing functions and a `setup`/`draw` structure similar to [Processing's](https://processing.org/examples/loop.html).
It is based on [SDL 2](https://www.libsdl.org/).

**Why write a wrapper around SDL?**
First semester students typically don't know about double buffering or window handles.
This thin wrapper removes the need for explaining such things, which would only keep the teacher from explaining the stuff that really counts.

**Why an additional tool?**
Well, since we are using a couple of libraries, the gcc command becomes quite heavy: e.g. `gcc test.c -o test $(sdl2-config --libs --cflags) -lSDL2_gfx`.
This is cumbersome to type and adds a lot of room for error. The `sta` tool shall reduce errors during compiling.
Also it prescribes a folder structure, which makes it easier for the students to keep their files tidy and allows the teacher to easily find files on _everyone's_ computer.

## Installation

Lots to do here...

<!-- * on mac: i installed `brew install sdl2 sdl2_gfx` -->

<!-- I need gfx for drawing ellipses. -->
<!-- for reference: open /usr/local/Cellar/sdl2_gfx/1.0.0/include/ -->

## Get started

In order to get started we create a new project with the `sta` tool:

```bash
sta new myprj
# => Created a new folder: ~/Documents/STA/myprj
# => Initialized new folder with template default
# => To get started run: ...
```

The assistant has now created a number of files in the STA folder. The most important file is named after the project. Here this is `myprj.c` and it looks like this:

```c
#include "includes/sta.h"

void setup() {
  // do initialization here
}

void draw() {
  // this will be repeated on and on and on...
}
```

Let's do something with the program and change the contents of the file to:

```c
#include "includes/sta.h"

void setup() {
  background(50,50,50);
}

void draw() {
  fill(100, frame_no % 255, frame_no % 255); // set the fill color
  rectangle(frame_no*5, frame_no, frame_no, frame_no*10); // draw a rectangle (filled with stroke)
  delay(40); // wait a bit, so we see the whole thing build up
}
```

Now all left to do is to compile and run the program. Here the assistant helps again:

```bash
cd ~/Documents/STA/myprj # let's not forget that we have to go to the project first
sta build # runs gcc with all the -I and -l options and writes the executable to myprj
# ... output of GCC ...
sta run # just calls ./myprj
```

## The default template

TODO: Document the drawing API here.

## Internals

**Templates**
The templates folder can contain multiple templates.
If no other option is chosen, the `default` template will be used.
When a new project is created all files & folders are copied to the (new) project folder.

A template must have at least one file which is named after the template's name (with extension `.c`).
This file will then be renamed from `TEMPLATE_NAME.c` to `PROJECT_NAME.c`.
Optionally, there can be a `gcc.opts` file. This file is evaluated in the bash (yes it may contain shell substitutions) and added to arguments when running `gcc`.

**Updates**
The templates are kept under `~/.sta/templates/*`. If one calls `sta update` (while having internet), the latest version of templates is pulled from `http://github.com/motine/sta`.
Updating existing projects is currently not supported.

**Testing**
While developing/testing the `sta` tool, I did not want to re-create new projects with `sta new` all the time.
Hence, I use the following workflow: `cd templates/default; ../../sta build`

## TODO

* vagrant: Create ubuntu with Desktop (folder shall include all C code)
* Add installation manual
* Add features to `sta`:
  * `new`: create a new folder with template inside.
    Rename `default.c` to `project_name.c`.
    All projects are assumed under `~/Documents/STA/PROJECT_NAME/`.
  * `update`: download the latest version of the sta script and download new templates and headers/c files from github.
    Keep the templates under `~/.sta/templates/*`.
* Add features to wrapper `drawing.h`
  * set the color for stroke and fill
  * draw ellipses, rects, lines (filled _and_ outlines, mind the previously set color)
  * have a random() and millis() function
  * have key and mouse handling (variables can be queried by the loop, e.g. `if (mousePressed) ...`
  * add error checking everywhere

