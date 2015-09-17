#ifndef SKETCHBOOK_H
#define SKETCHBOOK_H

#include <stdbool.h> // we want to use booleans
#include <SDL.h>
#include "drawing.h"
#include "input.h"
#include "misc.h"

// The sketchbook brings up the main window and provides the main functions.
// It will will expects a `void setup()` and a `void draw()` function to be defined somewhere else (in the student's program).

// forward declarations for methods which need to be defined by the student
// this method is not implemented in the c file!
void setup();
// this method is not implemented in the c file!
void draw();

// stop re-drawing. the result of the last image will be kept on the screen.
void stop();
// terminate the application
void quit();

// returns the number of the frame which is currently shown/drawn.
// The result of the first draw method has frame index 0, the next 1, ...
unsigned long long frame_index();

// set the color for the background used to clear the screen before each `draw()` call.
void background(uint8_t r, uint8_t g, uint8_t b);

// --- internals
#define WIDTH 800
#define HEIGHT 600
#define FRAME_DURATION 20 // ms, determines the frame rate (1000/frame rate). If set it to 20 ms we have 50 fps (1000ms / 50frames = 20ms/frame).

extern SDL_Window* window;
extern SDL_Renderer* renderer;

// called by main to initialize the window
void init();
// called by main start the main run loop
void run();
// C's main function
int main();

#endif
