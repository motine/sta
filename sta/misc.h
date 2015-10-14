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

// simple debugging facility
void add_debug_line(const char *line); // forward declaration needed for debug

#define DEBUG_BUFFER_LENGTH 100
#define DEBUG_MAX_LINES 25

// Add a inspection to the debug overlay ("prefix: value").
// Right before the draw function is called, the overlay will be cleared.
// This means this method can be called multiple times during draw, but only the
// inspections added in the last draw will be shown.
// The overlay will be drawn after the draw method ran.
#define debug(PREFIX, VALUE)                                                   \
  {                                                                            \
    char buffer[DEBUG_BUFFER_LENGTH];                                          \
    char format[10] = "%s: ";                                                  \
    strcat(format, _Generic((VALUE), int : "%i",                               \
                            unsigned int : "%u",                               \
                                   float : "%f",                               \
                                  double : "%lf",                              \
                                   short : "%hi",                              \
                          unsigned short : "%hu",                              \
                                    long : "%li",                              \
                           unsigned long : "%lu",                              \
                               long long : "%lli",                             \
                      unsigned long long : "%llu"));                           \
    sprintf(buffer, format, PREFIX, VALUE);                                    \
    add_debug_line(buffer);                                                    \
  }

// shows the current frame rate (per second) as debug output.
void show_fps();

#endif
