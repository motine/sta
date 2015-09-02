// $ gcc test.c -o test `sdl2-config --libs --cflags` -lSDL2_gfx
// $ ./test

#include "includes/sta.h"

void setup() {
  background(50,50,50);
}

int i = 0;
void loop() {
  fill(100, i*2, i*2);
  rectangle(i*5, i, i, i*10);
  delay(40);
  i++;
}
