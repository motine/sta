#ifndef MISC_H
#define MISC_H

// waits the given number of milliseconds
void delay(unsigned int ms);
// returns the milliseconds passed since the program started (since reset_millis was called)
unsigned long long millis();

// initializes some stuff
void init_misc();
#endif
