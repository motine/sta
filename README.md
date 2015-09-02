# Simple Teaching Assistant

**This is not ripe yet. I will add more documentation as soon as I get somewhere with this project.**

The Simple Teaching Assistant help to teach programming.
Our students will become engineers, so we chose `C` as language.
But there is an allure to projects like [Processing](https://processing.org/), which teach programming a little more visual – and a little less black matrix.

The Simple Teaching Assistant takes the edge off of graphical programming by providing a ready-made environment.
The `sta` tool lets the student easily create projects and compile them.
These (new) projects are derived from a template. 
The default template offers a set of simple drawing functions and a `setup`/`draw` structure similar to [Processing's](https://processing.org/examples/loop.html).
It is based on [SDL 2](https://www.libsdl.org/).

**Why write a wrapper around SDL?**
First semester students typically don't know about double buffering, window handles or texture rendering.
The thin wrapper removes the need for explaining such things and gives the students simple drawing tools to solve (visual) problems.
Hence, we, the teachers, can focus on explaining the stuff that really counts: problem solving.

**Why an additional tool?**
Well, since we are using a couple of libraries, the gcc command becomes quite heavy: `gcc test.c -o test $(sdl2-config --libs --cflags) -lSDL2_gfx`.
This line is cumbersome to type and adds a lot of room for error. The `sta` tool shall reduce errors during compiling.
Also it prescribes a folder structure, which makes it easier for students to keep their files tidy and allows the teacher to easily find files on _everyone's_ computer.

## Installation

**On Mac**, you can install the libraries via [homebrew](http://brew.sh/):  `brew install sdl2 sdl2_gfx`. Or do it manually: [sdl 2](https://www.libsdl.org/download-2.0.php) and [sdl2 gfx](http://cms.ferzkopp.net/index.php/software/13-sdl-gfx).

**On Linux** (Ubuntu), I installed the following packages: `libsdl2 libsdl2-dev libsdl2-gfx-dev`.

<!-- I need gfx for drawing ellipses. -->
<!-- for reference: open /usr/local/Cellar/sdl2_gfx/1.0.0/include/ -->

## Get started

In order to get started we create a new project with the `sta` tool:

```bash
sta new myprj
# => Created a new folder: ~/Documents/sta/myprj
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
void draw() {
  rectangle(10, 10, 400, 300);
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

### Examples

#### Full setup and frame count

```c
#include "includes/sta.h"

void setup() {
  // remove background
  background(0, 0, 0); 
  // set colors
  fill(100, 50, 50); 
  stroke(200, 200, 255);
}

void draw() {
  rectangle(frame_no*5 % 300, 10, 400, 300); // draw a rect
  delay(100); // wait a bit, so we see the whole thing build up
}
```

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

**Vagrant**
For testing the environment of the students I am using a vagrant machine.
To start the minimalistic window manager please run `sudo startxfce4` in the GUI.

## TODO

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
  * add text()
  * use fill color for background()
  * have key and mouse handling (variables can be queried by the loop, e.g. `if (mousePressed) ...`
  * add error checking everywhere
  * Add API documentation to README
