#ifndef MISC_H
#define MISC_H

// waits the given number of milliseconds
void delay(unsigned int ms);
// returns the milliseconds passed since the program started (since reset_millis was called)
long long millis();

// initializes the millis counter, only to be used by drawing.c
void reset_millis();
#endif
