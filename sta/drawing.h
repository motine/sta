#ifndef DRAWING_H
#define DRAWING_H

// Provides drawing functions for the sketchbook.
// It is a thin wrapper arount the GFX library.

#include <stdint.h>
#include <math.h> // include PI by default

// Set fill color for drawing future shapes.
void fill(uint8_t r, uint8_t g, uint8_t b);
// Disable filling shapes.
void no_fill();
// Set stroke color for drawing future shapes.
void stroke(uint8_t r, uint8_t g, uint8_t b);
// Disable stroking future shapes.
void no_stroke();

// Draws a line from (x1, y1) to (x2, y2) with the stroke color.
void line(unsigned int x1, unsigned int y1, unsigned int x2, unsigned int y2);
// Draws a rectangle from (x1, y1) to (x2, y2).
void rectangle(unsigned int x1, unsigned int y1, unsigned int x2, unsigned int y2);
// Draws an ellipse around (x, y) with the radius of rx and ry.
void ellipse(unsigned int x, unsigned int y, unsigned int rx, unsigned int ry);
// Draws a circle with its midpoint at (x, y) and radius r.
void circle(unsigned int x, unsigned int y, unsigned int r);
// Draws a pie piece around the midpoint (x,y) and radius r. Start and end angle are given in degrees
void pie(unsigned int x, unsigned int y, unsigned int r, unsigned int start, unsigned int end);
// Sets the given pixel to the stroke color.
void pixel(unsigned int x, unsigned int y);

#define DEFAULT_FONT_SIZE 20 // pt
// Draws the given text at (x,y), using the stroke color.
void text(unsigned int x, unsigned int y, const char* text);

// initializes some stuff
void drawing_init();
void drawing_loop();
void drawing_free();

#endif
