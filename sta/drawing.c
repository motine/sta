#include "drawing.h"
#include "sketchbook.h"
#include <SDL2_gfxPrimitives.h>
#include <SDL_ttf.h>

// -- colors
static uint8_t fill_r, fill_g, fill_b, fill_a;
static uint8_t stroke_r, stroke_g, stroke_b, stroke_a;

void default_stoke() {
  stroke_r = 0x66;
  stroke_g = 0x66;
  stroke_b = 0x66;
  stroke_a = 0xFF;
}
void default_fill() {
  fill_r = 0xFF;
  fill_g = 0xFF;
  fill_b = 0xFF;
  fill_a = 0xFF;
}

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

void triangle(unsigned int x1, unsigned int y1, unsigned int x2, unsigned int y2, unsigned int x3, unsigned int y3) {
  aatrigonRGBA(renderer, x1, y1, x2, y2, x3, y3, stroke_r, stroke_g, stroke_b, stroke_a);
  filledTrigonRGBA(renderer, x1, y1, x2, y2, x3, y3, fill_r, fill_g, fill_b, fill_a);
}

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

// -- text
static TTF_Font* standard_font;

void text(unsigned int x, unsigned int y, const char* text) {
  if (strlen(text) <= 0)
    return;
  SDL_Color color = {stroke_r, stroke_g, stroke_b, 0};

  SDL_Surface* surface = TTF_RenderText_Blended(standard_font, text, color);
  int surface_width = surface->w;
  int surface_height = surface->h;
  SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, surface);
  SDL_FreeSurface(surface);

  SDL_Rect dest_rect = {x, y, surface_width, surface_height};
  SDL_RenderCopy(renderer, texture, NULL, &dest_rect);

  SDL_DestroyTexture(texture);
}

void drawing_init() {
  TTF_Init();
  standard_font = TTF_OpenFont("sta/fonts/Courier_Prime_Bold.ttf", 20);
}

void drawing_loop() {
  default_stoke();
  default_fill();
}

void drawing_free() {
  TTF_CloseFont(standard_font);
  TTF_Quit();
}
