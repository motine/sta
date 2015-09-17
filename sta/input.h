#ifndef INPUT_H
#define INPUT_H

#include <stdbool.h>

// Returns the current x mouse cooridinate.
unsigned int mouse_x();
// Returns the current y mouse cooridinate.
unsigned int mouse_y();
// Returns true if the left mouse button is pressed.
bool mouse_pressed();

// Returns true if the given key is pressed.
// Valid keys are found in the "SDL_Scancode Value" column of this table: https://wiki.libsdl.org/SDL_Scancode
// Be aware: The ESC key is handled by the framework itself and will quit the application.
bool key_pressed(uint8_t key);

#endif
