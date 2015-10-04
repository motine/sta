#include "misc.h"
#include <sys/time.h>
#include <time.h>
#include <stdlib.h>
#include "sketchbook.h"

static unsigned long long start_millis = 0;

unsigned long long millis() {
  struct timeval tv;
  gettimeofday(&tv, NULL);
  return (tv.tv_sec) * 1000 + (tv.tv_usec) / 1000 - start_millis;
}


// simple debugging facility
static char debug_lines[DEBUG_MAX_LINES][DEBUG_BUFFER_LENGTH];
static unsigned int debug_next_line_index;

void debug_clear() {
  debug_next_line_index = 0;
  for (unsigned short i=0; i < DEBUG_MAX_LINES; i++) {
    strcpy(debug_lines[i], "");
  }
}

void debug_draw() {
  for (unsigned short i=0; i < debug_next_line_index; i++) {
    text(50, 50 + i*20, debug_lines[i]);
  }
}

void add_debug_line(const char* line) {
  if (debug_next_line_index < DEBUG_MAX_LINES) {
    strcpy(debug_lines[debug_next_line_index], line);
    debug_next_line_index++;
  } // silently fail if there is too many lines added in one loop
}

// life cycle methods
void misc_init() {
  srand(time(NULL));
  start_millis = millis();
}

void misc_loop_start() {
  debug_clear();
}
void misc_loop_end() {
  debug_draw();
}