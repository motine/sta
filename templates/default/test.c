// $ gcc test.c -o test `sdl2-config --libs --cflags` -lSDL2_gfx
// $ ./test

#include <stdio.h>
#include "SDL.h"
#include "SDL2_gfxPrimitives.h"
const unsigned int WIDTH = 800;
const unsigned int HEIGHT = 600;

static SDL_Window* window;
static SDL_Renderer* renderer;
void init() {
  SDL_Init(SDL_INIT_VIDEO);
  window = SDL_CreateWindow("Your Program", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, WIDTH, HEIGHT, SDL_WINDOW_OPENGL);
  if (window == NULL) {
    // error
  }
  renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
}

void run() {
  // int run = 1;
  // SDL_Event event;
  // while (run) {
  //   SDL_PollEvent(&event);
  //   if (event.type == SDL_QUIT) {
  //     run = 0;
  //   }
  // }
  SDL_Delay(1000); // TODO remove when we start the real event loop
  SDL_DestroyWindow(window);
  SDL_Quit(); 
}

static Uint32 fill_color;
Uint32 rgb(uint8_t r, uint8_t g, uint8_t b) {
  // colors are #ARGB
  Uint32 result = 0xFF << 24;
  return result | b << 16 | g << 8 | r;
}
void fill(uint8_t r, uint8_t g, uint8_t b) {
  fill_color = rgb(r,g,b);
}

void background(uint8_t r, uint8_t g, uint8_t b) {
  SDL_SetRenderDrawColor(renderer, r,g,b,0xFF);
  SDL_RenderClear(renderer); // TODO this is a very ugly way to deal with the double buffering
  SDL_RenderPresent(renderer); // TODO read when you have internet and also change below
  SDL_RenderClear(renderer);
}

void rectangle(unsigned int x1, unsigned int y1, unsigned int x2, unsigned int y2) {
  SDL_SetRenderDrawColor(renderer, r,g,b,0xFF);
  boxColor(renderer, x1, y1, x2, y2, fill_color);
  SDL_RenderPresent(renderer);
  boxColor(renderer, x1, y1, x2, y2, fill_color);
}
// rectangleColor(renderer, i*5, 0, i*5 + 100, 100, 0xFF0000FF);

void delay(unsigned int ms) {
  SDL_Delay(ms);
}

int main() {
  init();
  // Uint32 stroke = ;
  background(50,50,50);
  fill(100, 100, 255);
  for (int i=0; i < 100; i++) {
    fill(100, i*2, i*2);
    rectangle(i*5, i, i, i*10);
    delay(40);
  }

  run();
	return 0;
}
