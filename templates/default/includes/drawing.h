#ifndef DRAWING_H
#define DRAWING_H

// We need to be careful with double buffering:
// Since we have "two" pictures, we flip the page/buffer for each drawing operation.
// This is not nice and may lead to flickering, but (!) we get around explaining double buffering.
// For the students, this omission is very benficial, because they can focus on what counts: drawing stuff.

#include <stdio.h>
#include "SDL.h"
#include "SDL2_gfxPrimitives.h"

// let's keep WIDTH and HEIGHT constant.
const unsigned int WIDTH = 800;
const unsigned int HEIGHT = 600;

// forward declarations for methods which need to be defined by the student.
void setup();
void draw();

// There will be only one window... For now...
static SDL_Window* window;
static SDL_Renderer* renderer;

static unsigned long frame_no = 0; // number of frames since the program started

void init() {
  SDL_Init(SDL_INIT_VIDEO);
  window = SDL_CreateWindow("Your Program", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, WIDTH, HEIGHT, SDL_WINDOW_SHOWN);
  renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
  setup();
}

// start the main loop and handle ESC
void run() {
  int run = 1;
  printf("Please hit ESC in the main window to exit the program.\n");
  SDL_Event event;
  while (run) {
    SDL_PollEvent(&event);
    if (event.type == SDL_QUIT) {
      run = 0;
    }
    if ((event.type == SDL_KEYDOWN) && (event.key.keysym.sym == SDLK_ESCAPE)) {
      run = 0;
      return;
    }
    draw();
    frame_no++;
  }
  SDL_DestroyWindow(window);
  SDL_Quit(); 
}

// colors
static Uint32 fill_color;
static Uint32 stroke_color;

Uint32 rgb(uint8_t r, uint8_t g, uint8_t b) {
  // colors are #ARGB
  Uint32 result = 0xFF << 24;
  return result | b << 16 | g << 8 | r;
}

void fill(uint8_t r, uint8_t g, uint8_t b) {
  fill_color = rgb(r,g,b);
}

// drawing functions
void background(uint8_t r, uint8_t g, uint8_t b) {
  SDL_SetRenderDrawColor(renderer, r,g,b,0xFF);
  for (uint8_t i=0; i<2; i++) {
    SDL_RenderClear(renderer); // TODO this is a very ugly way to deal with the double buffering
    if (i==0)
      SDL_RenderPresent(renderer); // TODO read when you have internet and also change below
  }
}

void rectangle(unsigned int x1, unsigned int y1, unsigned int x2, unsigned int y2) {
  for (uint8_t i=0; i<2; i++) {
    boxColor(renderer, x1, y1, x2, y2, fill_color);
    if (i==0)
      SDL_RenderPresent(renderer);
  }
}

// misc
void delay(unsigned int ms) {
  SDL_Delay(ms);
}

int main() {
  init();
  run();
	return 0;
}

#endif
