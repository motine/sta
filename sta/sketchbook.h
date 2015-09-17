#ifndef SKETCHBOOK_H
#define SKETCHBOOK_H

#include <stdbool.h> // we want to use booleans
#include <SDL.h>
#include "drawing.h"
#include "input.h"
#include "misc.h"

// The sketchbook brings up the main window and provides the main functions.
// It will will expects a `void setup()` and a `void draw()` function to be defined somewhere else (in the student's program).

// Called once before the calls to `draw` start.
void setup(); // !! This method must be provided by the student (in the `project.c` file).

// This method is called over and over again.
// Right before the screen is emtied, right after all the drawing is put on the screen. 
void draw(); // !! This method must be provided by the student (in the `project.c` file)

// Stop the calls to `draw`. The result of the current `draw` will be kept on the screen forever.
void stop();
// Terminate the application after the current `draw`.
void quit();

// Returns the number of the frame which is currently drawn.
// The result of the first draw method has frame index 0, the next 1, ...
unsigned long long frame_index();

// Set the background color. It is used to clear the screen before each `draw()` call.
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
