// $ gcc test.c -o test `sdl2-config --libs --cflags` -lSDL2_gfx
// $ ./test

#include "includes/sta.h"

void setup() {
  background(50,50,50);
}

void draw() {
  fill(100, frame_no % 255, frame_no % 255);
  rectangle(frame_no*5, frame_no, frame_no, frame_no*10);
  delay(40);
}
