#ifndef MISC_H
#define MISC_H

// Returns the number of milliseconds passed since the program started.
unsigned long long millis();

#define MIN(X, Y) (((X) < (Y)) ? (X) : (Y))
#define MAX(X, Y) (((X) > (Y)) ? (X) : (Y))

// initializes some stuff
void misc_init();

#endif
