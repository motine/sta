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
#define DEBUG_MAX_LINES 25
#define DEBUG_BUFFER_LENGTH 100

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

#define DEBUG_IMPL(FORMAT) { char buffer[DEBUG_BUFFER_LENGTH]; sprintf(buffer, "%s: "#FORMAT, prefix, value); add_debug_line(buffer); }

void debugi(const char* prefix, int value) DEBUG_IMPL(%i);
void debugui(const char *prefix, unsigned int value) DEBUG_IMPL(%ui);
void debugl(const char *prefix, long value) DEBUG_IMPL(%li);
void debugul(const char *prefix, unsigned long value) DEBUG_IMPL(%lui);
void debugll(const char *prefix, long long value) DEBUG_IMPL(%lli);
void debugull(const char *prefix, unsigned long long value) DEBUG_IMPL(%llui);
void debugs(const char *prefix, short value) DEBUG_IMPL(%hi);
void debugus(const char *prefix, unsigned short value) DEBUG_IMPL(%hui);
void debugf(const char *prefix, float value) DEBUG_IMPL(%f);
void debugd(const char *prefix, double value) DEBUG_IMPL(%lf);
void debugld(const char *prefix, long double value) DEBUG_IMPL(%Lf);

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