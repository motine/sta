#include "misc.h"
#include <sys/time.h>
#include "sketchbook.h"

void delay(unsigned int ms) {
  SDL_Delay(ms);
}

static long long start_millis = 0;
void reset_millis() {
  start_millis = millis();
}
long long millis() {
  struct timeval tv;
  gettimeofday(&tv, NULL);
  return (tv.tv_sec) * 1000 + (tv.tv_usec) / 1000 - start_millis;
}
