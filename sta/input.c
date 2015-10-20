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

bool mouse_pressed() {
  return SDL_GetMouseState(NULL, NULL) & SDL_BUTTON(SDL_BUTTON_LEFT);
}

// scancode is the pysical key location
// keycode is what it means (after applying keyboard layout)

const SDL_Keycode KEYCODES_TO_TEST[] = {
  SDLK_0, SDLK_1, SDLK_2, SDLK_3, SDLK_4, SDLK_5, SDLK_6, SDLK_7, SDLK_8, SDLK_9,
  SDLK_a, SDLK_b, SDLK_c, SDLK_d, SDLK_e, SDLK_f, SDLK_g, SDLK_h, SDLK_i, SDLK_j,
  SDLK_k, SDLK_l, SDLK_m, SDLK_n, SDLK_o, SDLK_p, SDLK_q, SDLK_r, SDLK_s, SDLK_t,
  SDLK_u, SDLK_v, SDLK_w, SDLK_x, SDLK_y, SDLK_z };

const unsigned keycodes_to_test_length = sizeof(KEYCODES_TO_TEST) / sizeof(SDL_Keycode);

char key_pressed() {
  // this is not the most elegant way of checking for keys.
  // one would probably go and poll for events in the event loop and only react to the key once.
  // however, I wanted this to feel similar to the mouse functions.
  const uint8_t *state = SDL_GetKeyboardState(NULL); // this returns a map of scancodes
  for (unsigned int i = 0; i < keycodes_to_test_length; i++) {
    SDL_Scancode sc = SDL_GetScancodeFromKey(KEYCODES_TO_TEST[i]);
    if (state[sc]) {
      return KEYCODES_TO_TEST[i];
    }
  }
  return 0;
}