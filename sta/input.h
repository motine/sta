#ifndef INPUT_H
#define INPUT_H

#include <stdbool.h>

// Returns the current x mouse cooridinate.
unsigned int mouse_x();
// Returns the current y mouse cooridinate.
unsigned int mouse_y();
// Returns true if the left mouse button is pressed.
bool mouse_pressed();

// Returns the character which is currently pressed on the keyboard.
// We can only recognize lowercase alphabetic letters and numbers ('a', 'b', 'c', ..., 'z', '0', '1', ..., '9').
// Key modifiers are not considered (shift, ctrl, alt, etc.).
// If none is pressed, this function returns 0.
char key_pressed();

#endif
