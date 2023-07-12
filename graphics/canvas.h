
/*
  NOTE: this solution is greatly based on the OLIVE.C project from Tsoding,
        where he also makes a in memory based graphics solution. As this is
        made to further my own understanding of C coding, so the direct copying
        is minimal. But it can happen.

  LINK: https://github.com/tsoding/olive.c

        Link is to the original repo from Tsoding, please check it out, if you
        want a more compleat/better graphics lib.

*/

#include <stdlib.h>
#include <stdint.h>

#ifndef _CANVAS_DEFINITION
#define _CANVAS_DEFINITION

#define CANVAS_GET_PIXEL(cs, x, y) (cs).cv[ (y)*(cs).stride + (x) ]
#define SIGN(T, n) ((T)((n) > 0) - (T)(n) < 0)
#define ABS(T, n) (SIGN(T, n)*(n))

#ifndef CANVAS_ALLOC
#define CANVAS_ALLOC malloc
#endif // CANVAS_ALLOC

#ifndef CANVAS_FREE
#define CANVAS_FREE free
#endif // CANVAS_FREE

#ifndef CANVAS_MEMSET
#define CANVAS_MEMSET memset
#endif // CANVAS_MEMSET

typedef struct {
  size_t rows, cols;
  size_t stride;
  uint32_t *cv;
} Canvas;

// NOTE: this part, and its relevant function is completly riped
//       from the original repo.
typedef struct {
  int x1, y1;
  int x2, y2;
  
  int ox1, oy1;
  int ox2, oy2;
} Normalized_Rect;

Canvas *CANVAS_create_canvas(size_t cols, size_t rows);
Canvas *CANVAS_create_sub_canvas(Canvas *this, size_t x, size_t y, size_t cols, size_t rows);

int CANVAS_normalize_rect(int x, int y, int w, int h, Canvas *cv, Normalized_Rect *nr);

void CANVAS_print(Canvas *this);

void CANVAS_clear(Canvas *this);
void CANVAS_free(Canvas *this);

#endif // _CANVAS_DEFINITION

