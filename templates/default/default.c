#include "sketchbook.h"
#include "drawing.h"
#include "misc.h"

void setup() {
  // do initialization here
}

#include <stdio.h>
static int i = 0;
void draw() {
  // this will be repeated on and on and on...
  rectangle(i % 300,30,300,300);
  i++;
  printf("%d\n", millis());
  
}
