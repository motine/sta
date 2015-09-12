#ifndef SKETCHBOOK_H
#define SKETCHBOOK_H

// The sketchbook brings up the main window and provides the main functions.
// It will will expects a `void setup()` and a `void draw()` function to be defined somewhere else (in the student's program).

#include "SDL.h"
#include "drawing.h"
#include "misc.h"

#define WIDTH 800
#define HEIGHT 600
#define FRAME_DURATION 20 // ms, Determines the frame rate (1000/frame rate). If set it to 20 ms we have 50 fps (1000ms / 50frames = 20ms/frame).

extern SDL_Window* window;
extern SDL_Renderer* renderer;

void init();
void run();
int main();

// set the color for the background
void background(uint8_t r, uint8_t g, uint8_t b);

#endif
