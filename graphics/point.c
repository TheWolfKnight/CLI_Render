
#include <stdlib.h>

#include "./point.h"

#ifndef _CANVAS_POINT_IMPLIMENTATION
#define _CANVAS_POINT_IMPLIMENTATION

Point POINT_new(int x, int y) {
  Point p = {
    .x = x,
    .y = y,
  };
  return p;
}

#endif // _CANVAS_POINT_IMPLIMENTATION

