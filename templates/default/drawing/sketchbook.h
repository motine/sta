#ifndef GRAPHICS_H
#define GRAPHICS_H

// The sketchbook brings up the main window and provides the main functions.
// It will will expects a `void setup()` and a `void draw()` function to be defined somewhere else (in the student's program).

#include "SDL.h"

#define WIDTH 800
#define HEIGHT 600

extern SDL_Window* window;
extern SDL_Renderer* renderer;

void init();
void run();
int main();

// set the color for the background
void background(uint8_t r, uint8_t g, uint8_t b);

#endif
