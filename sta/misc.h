#ifndef MISC_H
#define MISC_H

// Returns the number of milliseconds passed since the program started.
unsigned long long millis();

#define MIN(X, Y) (((X) < (Y)) ? (X) : (Y))
#define MAX(X, Y) (((X) > (Y)) ? (X) : (Y))

// initializes some stuff
void misc_init();
void misc_loop_start();
void misc_loop_end();

// simple debugging facility:

// Add a inspection to the debug overlay ("prefix: value").
// Right before the draw function is called, the overlay will be cleared.
// This means this method can be called multiple times during draw, but only the inspections added in the last draw will be shown.
// The overlay will be drawn after the draw method ran.
#define debug(PREFIX, VALUE) _Generic((VALUE), \
    int : debugi,                              \
    unsigned int : debugui,                    \
    long : debugl,                             \
    unsigned long : debugul,                   \
    long long : debugll,                       \
    unsigned long long : debugull,             \
    short : debugs,                            \
    unsigned short : debugus,                  \
    float : debugf,                            \
    double : debugd,                           \
    long double : debugld)(PREFIX, VALUE)

void debugi(const char* prefix, int value);
void debugui(const char *prefix, unsigned int value);
void debugl(const char *prefix, long value);
void debugul(const char *prefix, unsigned long value);
void debugll(const char *prefix, long long value);
void debugull(const char *prefix, unsigned long long value);
void debugs(const char *prefix, short value);
void debugus(const char *prefix, unsigned short value);
void debugf(const char *prefix, float value);
void debugd(const char *prefix, double value);
void debugld(const char *prefix, long double value);
#endif
