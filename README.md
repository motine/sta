# Simple Teaching Assistant

**This is not ripe yet. I will add more documentation as soon as I get somewhere with this project.**

The Simple Teaching Assistant helps in bringing programming to students.
Since our students will become engineers, we chose `C` as a language.
But there is an allure to projects like [Processing](https://processing.org/), which teach programming a little more visual.

The Simple Teaching Assistant takes the edge off of graphical programming by providing a ready-made environment.
The `sta` tool lets the student easily create projects (in a prescribed folder structure) and compile them.
These (new) projects are derived from a template. 
The default template offers a set of simple drawing functions and a `setup`/`draw` structure similar to [Processing's](https://processing.org/examples/loop.html).
It is based on [SDL 2](https://www.libsdl.org/).

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
  // do initialization herre
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
sta build
# ... output of GCC ...
sta run
```

## TODO

* vagrant: create ubuntu with desktop (folder shall include all C code)
* Write tool `sta` (see notes there)
* Write wrapper `sta.h` (see notes there)

