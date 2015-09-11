#include "sketchbook.h"
#include <SDL.h>
#include <stdio.h>
#include "drawing.h"

SDL_Window* window;
SDL_Renderer* renderer;

// forward declarations for methods which need to be defined by the student.
void setup();
void draw();

// Window and loop stuff
static unsigned long frame_no = 0; // number of frames since the program started
static uint8_t background_r = 0xCC, background_g = 0xCC, background_b = 0xCC;

void init() {
  SDL_Init(SDL_INIT_VIDEO);
  window = SDL_CreateWindow("sketchbook", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, WIDTH, HEIGHT, SDL_WINDOW_SHOWN);
  renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
  setup();
}

void background(uint8_t r, uint8_t g, uint8_t b) {
  background_r = r;
  background_g = g;
  background_b = b;
}


// start the main loop and handle ESC
void run() {
  int run = 1;
  printf("Please hit ESC in the main window to exit the program.\n");
  SDL_Event event;
  while (run) {
    SDL_SetRenderDrawColor(renderer, background_r, background_g, background_b, 0xFF);
    SDL_RenderClear(renderer);
    SDL_PollEvent(&event);
    if (event.type == SDL_QUIT) {
      run = 0;
    }
    if ((event.type == SDL_KEYDOWN) && (event.key.keysym.sym == SDLK_ESCAPE)) {
      run = 0;
      return;
    }
    draw();
    SDL_RenderPresent(renderer);
    frame_no++;
  }
  SDL_DestroyWindow(window);
  SDL_Quit(); 
}

int main() {
  init();
  run();
	return 0;
}
