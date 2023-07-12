
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "./canvas.h"

#include "../global.h"

#ifndef _CANVAS_IMPLIMENTATION
#define _CANVAS_IMPLIMENTATION

Canvas *CANVAS_create_canvas(size_t cols, size_t rows) {
  Canvas *c = CANVAS_ALLOC(sizeof(Canvas));
  c->rows = rows;
  c->cols = cols;
  c->stride = cols;

  int total_cells = rows * cols;
  c->cv = malloc(sizeof(uint32_t) * total_cells);
  memset(c->cv, 0, sizeof(uint32_t) * total_cells);

  return c;
}

Canvas *CANVAS_create_sub(Canvas *this, size_t x, size_t y, size_t rows, size_t cols) {
  Canvas *r = CANVAS_ALLOC(sizeof(Canvas));
  r->rows = rows;
  r->cols = cols;
  r->stride = x;
  r->cv = &CANVAS_GET_PIXEL(*this, x, y);
  return r;
}

int CANVAS_normalize_rect(int x, int y, int w, int h, Canvas *cv, Normalized_Rect *nr) {
  if (w == 0 || h == 0) return 0;

  nr->ox1 = x;
  nr->oy1 = y;

  // NOTE: calcualte the bounding box, and make sure that
  //       ox1 < ox2 & oy1 < oy2.

  // TODO: remove -1 to see the difference
  nr->ox2 = x + SIGN(int, w) * (ABS(int, w) - 1);
  if (nr->ox1 > nr->ox2) SWAP(int, nr->ox1, nr->ox2);
  nr->oy2 = y + SIGN(int, h) * (ABS(int, h) - 1);
  if (nr->oy1 > nr->oy2) SWAP(int, nr->oy1, nr->oy2);

  // NOTE: check to make sure the rect is inside the canvas
  if (nr->ox1 >= (int)cv->cols || nr->ox2 < 0 ||
      nr->oy1 >= (int)cv->rows || nr->oy2 < 0   )
    return 0;

  // NOTE: sets the actual positions, and clamps them inside the canvas

  nr->x1 = x < 0 ? 0 : x;

  nr->x2 = nr->ox2 >= (int)cv->cols ? (int)cv->cols-1 : nr->ox2;
  nr->y1 = y < 0 ? 0 : y;
  nr->y2 = nr->oy2 >= (int)cv->rows ? (int)cv->rows-1 : nr->oy2;

  return 1;
}

void CANVAS_print(Canvas *this) {
  for (int i = 0; i < this->rows; ++i) {
    for(int j = 0; j < this->cols; ++j) {
      uint32_t n = CANVAS_GET_PIXEL(*this, j, i);
      // if (n != 1 && n != 0)
      //   printf("row: %i, col: %i\n", j, i);
      printf("%i", n);
    }
    printf("\n");
  }
}

void CANVAS_clear(Canvas *this) {
  memset(this->cv, 0, sizeof(uint32_t) * this->rows * this->cols);
}

void CANVAS_free(Canvas *this) {
  CANVAS_FREE(this->cv);
  CANVAS_FREE(this);
}

#endif // _CANVAS_IMPLIMENTATION

