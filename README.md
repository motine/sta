# Simple Teaching Assistant

**This is not ripe yet. I will add more documentation as soon as I get somewhere with this project.**

The Simple Teaching Assistant help to teach programming.
Our students will become engineers, so we chose `C` as language.
But there is an allure to projects like [Processing](https://processing.org/), which teach programming a little more visual – and a little less black matrix.

The Simple Teaching Assistant takes the edge off of _graphical_ programming by providing a ready-made environment.
The provided framework lets the student easily create new graphical solutions and compile them.
The framework offers a set of simple drawing functions and a `setup`/`draw` structure similar to [Processing's](https://processing.org/examples/loop.html).
It is based on [SDL 2](https://www.libsdl.org/).

**Why write a wrapper around SDL?**
First semester students typically don't know about double buffering, window handles or texture rendering.
The thin wrapper removes the need for explaining such things and gives the students simple drawing tools to solve (visual) problems.
Hence, we, the teachers, can focus on explaining the stuff that really counts: problem solving.

## Installation

**On Mac**, you can install the prerequisites via [homebrew](http://brew.sh/):  `brew install git sdl2 sdl2_gfx`.

**On Linux** (Ubuntu), I installed the following packages: `git libsdl2 libsdl2-dev libsdl2-gfx-dev`.

Or do it manually: [sdl 2](https://www.libsdl.org/download-2.0.php) and [sdl2 gfx](http://cms.ferzkopp.net/index.php/software/13-sdl-gfx).

For offline usage (one student always has problems with his/her wifi), it is highly encouraged to check out the repository locally.
To do so, please go to:

```bash
sudo git clone https://github.com/motine/sta.git /usr/local/sta.git
# later you can then start a new project from the local repo:
# => git clone /usr/local/sta.git myproject
```

If you want to update a the local repository or an existing project you can run `git pull` in the respective folder.

## Get started

In order to get started we create a new project with:

```bash
cd ~/Documents
git clone https://github.com/motine/sta.git myproject # Creates a new folder: ~/Documents/myproject and copies the framework
```

The most important file is named `project.c`. This is where the student puts his/her solution. It starts off looking like this:

```c
#include "sketchbook.h"

void setup() {
  // do initialization here
}

void draw() {
  // this will be repeated on and on and on...
}
```

Let's do something with the program and change the contents of the draw function to:

```c
void draw() {
  rectangle(10, 10, 400, 300);
}
```

Now all left to do is to compile and run the program:

```bash
cd ~/Documents/myproject # let's not forget that we have to go to the project first
make # runs gcc with all the -I and -l options and writes the executable to 'project'
# ... output of GCC ...
./project # opens a window and shows a rectangle
```

# The framework

TODO write intro

## Overview

TODO add API docs / include header
TODO don't forget the functions and constants in sketchbook and misc (e.g. WIDTH)!

TODO document random (this is part of stdlib.h).

## Setup and draw

the drawing will only be shown on the screen after `draw`.

## Sketching functions

![](sta/imgs/funs.png)

```c
#include "sketchbook.h"

void setup() {
  // do initialization here
}

void draw() {
  // this will be repeated on and on and on...
  rectangle(10, 10, 200, 200);
  line(10, 20, 40, 10);
  ellipse(150, 60, 30, 20);
  circle(80, 150, 20);
  pie(60, 50, 30, 30, 180);
  pixel(100, 100);
}
```

## Frame rate

![](sta/imgs/fps.png)

The drawing sketchbook will ensure that there is a frame rate of 50 frames per second.
This ensures we have a near constant time between frames and the frame duration does not vary depending on the processors load.

```c
// ...
static int i = 0;
void draw() {
  rectangle(i % 100, 10, 100, 100);
  i++;
}
```

## Mouse & Keyboard

![](sta/imgs/mouse.png)

For the sake of simplicity, there is no event listeners or event polling. There are "just" functions to ask for the current mouse position and check which key is currently pressed.
This approach limits the keyboard input to only recognizing a single key at any given time.

```c
// ...
void draw() {
  rectangle(10, 10, mouse_x(), mouse_y());
}
```

![](sta/imgs/buttons.png)

Handling buttons and keys is done like this:

```c
// ...
void draw() {
  if (mouse_pressed()) { // checks if the left mouse button is pressed
    stroke(255, 0, 0);
  } else {
    stroke(200, 200, 200);
  }
  
  if (key_pressed(SDL_SCANCODE_RETURN)) { // checks if the enter key is pressed
    fill(255, 0, 0);
  } else {
    fill(255, 255, 255);
  }
  
  rectangle(10, 10, 100, 100);
}
```


## Coloring

![](sta/imgs/color.png)

_These are the worst colors a human ever chose..._

```c
#include "sketchbook.h"

void setup() {
  // do initialization here
}

void draw() {
  stroke(255, 0, 0); // apply stroke for all subsequent shapes
  line(10, 20, 40, 10); // appears red

  fill(0, 255, 0); // apply fill for all following shapes
  rectangle(10, 10, 150, 150); // has a green background and still red stroke

  stroke(0, 0, 255);
  no_fill(); // disable filling
  circle(50, 50, 20); // appears with blue stroke and not no fill

  no_stroke(); // disable stroking
  circle(10, 10, 10); // this is invisible
  
  stroke(0, 0, 0);
  pixel(100, 100); // adds three black pixels
  pixel(102, 100);
  pixel(104, 100);
}
```

# Internals

**Vagrant**
For testing the environment of the students I am using a vagrant machine.
To start the minimalistic window manager please run `sudo startxfce4` in the GUI.

## TODO

* Revise README.md
  * Add API documentation
  * add more examples
* Add features
  * add text()
  * have key and mouse handling (variables can be queried by the loop, e.g. `if (mousePressed) ...`, add `mouseX, ...`
  * add error checking everywhere
* Add style guides/rubocop + the same for c