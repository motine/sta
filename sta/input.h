#ifndef INPUT_H
#define INPUT_H

#include <stdbool.h>

// returns the x mouse cooridinate
unsigned int mouse_x();
// returns the y mouse cooridinate
unsigned int mouse_y();
// returns true if the left mouse button is pressed
bool mouse_pressed();

// returns true if the given key is pressed.
// valid keys are found in the "SDL_Scancode Value" column of this table: https://wiki.libsdl.org/SDL_Scancode
// Be aware: the ESC key is handled by the framework itself and will quit the application.
bool key_pressed(uint8_t key);

#endif
