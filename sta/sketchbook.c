#include "sketchbook.h"
#include <stdio.h>

SDL_Window* window;
SDL_Renderer* renderer;

// window and loop stuff
static unsigned long long frame_no = 0;  // number of frames since the program started
static uint8_t background_r = 0xCC, background_g = 0xCC, background_b = 0xCC;
static bool terminated = false;
static bool stopped = false;

void stop() {
  stopped = true;
}

void quit() {
  terminated = true;
}

unsigned long long frame_index() {
  return frame_no;
}

void background(uint8_t r, uint8_t g, uint8_t b) {
  background_r = r;
  background_g = g;
  background_b = b;
}

void init() {
  SDL_Init(SDL_INIT_VIDEO);
  window = SDL_CreateWindow("sketchbook", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, WIDTH, HEIGHT, SDL_WINDOW_SHOWN);
  renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
  drawing_init();
  misc_init();
  setup();
}

// start the main loop and handle ESC
void run() {
  printf("Please hit ESC in the main window to exit the program.\n");
  SDL_Event event;
  unsigned long long last_draw_millis = 0;
  while (!terminated) {
    // process events
    SDL_PollEvent(&event);
    if (event.type == SDL_QUIT) {
      break;
    }
    if ((event.type == SDL_KEYDOWN) && (event.key.keysym.sym == SDLK_ESCAPE)) {
      break;
    }
    if (stopped) {
      continue;
    }
    // draw (only if the frame rate demands it)
    if (millis() - last_draw_millis > FRAME_DURATION) {
      drawing_loop();
      misc_loop_start();
      SDL_SetRenderDrawColor(renderer, background_r, background_g, background_b, 0xFF);
      SDL_RenderClear(renderer);
      draw();
      misc_loop_end();
      SDL_RenderPresent(renderer);
      last_draw_millis = millis();
      frame_no++;
    }
  }
  drawing_free();
  SDL_DestroyWindow(window);
  SDL_Quit();
}

int main() {
  init();
  run();
  return 0;
}
