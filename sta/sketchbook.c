#include "sketchbook.h"
#include <stdio.h>

SDL_Window* window;
SDL_Renderer* renderer;

// window and loop stuff
static unsigned long long frame_no = 0;  // number of frames since the program started
static uint8_t background_r = 0xCC, background_g = 0xCC, background_b = 0xCC;
static bool terminated = false;
static bool stopped = false;
static bool shall_export_shots = false;
static unsigned int frame_duration = 40; // ms, determines the frame rate (1000/frame rate). If set it to 20 ms we have 50 fps (1000ms / 50frames = 20ms/frame).

void fps(float target_frames_per_sec) {
  frame_duration = 1000/target_frames_per_sec;
}

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

void export_shot() {
  char filename[100];
  sprintf(filename, "shots/%05llu.bmp", frame_no);
  int w, h;
  SDL_GetWindowSize(window, &w, &h);
  SDL_Surface *sshot = SDL_CreateRGBSurface(0, w, h, 32, 0x00ff0000, 0x0000ff00, 0x000000ff, 0xff000000);
  SDL_RenderReadPixels(renderer, NULL, SDL_PIXELFORMAT_ARGB8888, sshot->pixels, sshot->pitch);
  SDL_SaveBMP(sshot, filename);
  SDL_FreeSurface(sshot);
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
  bool battery_saver = false; // if enabled, each loop will end with a delay call
  while (!terminated) {
    // process events
    if (SDL_PollEvent(&event)) { // it may be that there is no event
      if ((event.type == SDL_QUIT) || ((event.type == SDL_KEYDOWN) && (event.key.keysym.sym == SDLK_ESCAPE))) {
        break;
      }
    }
    if (stopped) {
      continue;
    }
    // draw (only if the frame rate demands it; force draw in for the very first frame)
    if ((last_draw_millis == 0) || ((millis() - last_draw_millis) >= frame_duration)) {
      last_draw_millis = millis();
      drawing_loop();
      misc_loop_start();
      SDL_SetRenderDrawColor(renderer, background_r, background_g, background_b, 0xFF);
      SDL_RenderClear(renderer);
      draw();
      misc_loop_end();
      if (shall_export_shots) // export image
        export_shot();
      SDL_RenderPresent(renderer); // flip buffer
      frame_no++;
      battery_saver = false;
    } else {
      battery_saver = true;
    }
    if (battery_saver)
      SDL_Delay(1);
  }
  drawing_free();
  SDL_DestroyWindow(window);
  SDL_Quit();
}

int main(int argc, char **argv) {
  if (argc > 1) {
    if (strcmp("-s", argv[1]) == 0) {
      shall_export_shots = true;
    }
  }
  init();
  run();
  return 0;
}
