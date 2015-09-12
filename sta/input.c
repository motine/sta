#include "sketchbook.h"
#include "input.h"

unsigned int mouse_x() {
  int x;
  SDL_GetMouseState(&x, NULL);
  return x;
}

unsigned int mouse_y() {
  int y;
  SDL_GetMouseState(NULL, &y);
  return y;
}

int mouse_pressed() {
  return SDL_GetMouseState(NULL, NULL) & SDL_BUTTON(SDL_BUTTON_LEFT);
}

int key_pressed(uint8_t key) {
  const uint8_t* state = SDL_GetKeyboardState(NULL);
  return state[key];
}