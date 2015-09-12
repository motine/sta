#include "drawing.h"
#include "sketchbook.h"
#include <SDL2_gfxPrimitives.h>

// -- colors
static uint8_t fill_r = 0xFF, fill_g = 0xFF, fill_b = 0xFF, fill_a = 0xFF;
static uint8_t stroke_r = 0x66, stroke_g = 0x66, stroke_b = 0x66, stroke_a = 0xFF;

void fill(uint8_t r, uint8_t g, uint8_t b) {
  fill_r = r;
  fill_g = g;
  fill_b = b;
  fill_a = 0xFF;
}

void no_fill() {
  fill_a = 0x00;
}

void stroke(uint8_t r, uint8_t g, uint8_t b) {
  stroke_r = r;
  stroke_g = g;
  stroke_b = b;
  stroke_a = 0xFF;
}

void no_stroke() {
  stroke_a = 0x00;
}

// -- actual drawing
void line(unsigned int x1, unsigned int y1, unsigned int x2, unsigned int y2) {
  aalineRGBA(renderer, x1, y1, x2, y2, stroke_r, stroke_g, stroke_b, stroke_a);
}

void rectangle(unsigned int x1, unsigned int y1, unsigned int x2, unsigned int y2) {
  boxRGBA(renderer, x1, y1, x2, y2, fill_r, fill_g, fill_b, fill_a);
  rectangleRGBA(renderer, x1, y1, x2, y2, stroke_r, stroke_g, stroke_b, stroke_a);
}

void ellipse(unsigned int x, unsigned int y, unsigned int rx, unsigned int ry) {
  filledEllipseRGBA(renderer, x, y, rx, ry, fill_r, fill_g, fill_b, fill_a);
  aaellipseRGBA(renderer, x, y, rx, ry, stroke_r, stroke_g, stroke_b, stroke_a);
}

void circle(unsigned int x, unsigned int y, unsigned int r) {
  filledCircleRGBA(renderer, x, y, r, fill_r, fill_g, fill_b, fill_a);
  aacircleRGBA(renderer, x, y, r, stroke_r, stroke_g, stroke_b, stroke_a);
}

void pie(unsigned int x, unsigned int y, unsigned int r, unsigned int start, unsigned int end) {
  filledPieRGBA(renderer, x, y, r, start, end, fill_r, fill_g, fill_b, fill_a);
  pieRGBA(renderer, x, y, r, start, end, stroke_r, stroke_g, stroke_b, stroke_a);
}
// sets the given pixel to the stroke color
void pixel(unsigned int x, unsigned int y) {
  pixelRGBA(renderer, x, y, stroke_r, stroke_g, stroke_b, stroke_a);
}


