
#include <stdlib.h>
#include <stdio.h>

#include "./draw.h"
#include "./canvas.h"
#include "./point.h"

#include "../global.h"

#ifndef _CANVAS_DRAW_IMPLIMENTATION
#define _CANVAS_DRAW_IMPLIMENTATION

static FillType fill_type = FT_NO_FILL;
static uint32_t color = 0xFFFFFFFF;

static int i_clamp(int n, int min, int max) {
  n = n > max ? max : n;
  n = n < min ? min : n;
  return n;
}

void DRAW_set_fill(FillType ft) {
  fill_type = ft;
}

void DRAW_set_color(uint32_t cl) {
  color = cl;
}

static int DRAW_ellipse_no_fill(Canvas *this, int x, int y, int a, int b) {
  return 0;
}

// TODO: make work
int DRAW_ellipse(Canvas *this, int x, int y, int a, int b) {
  // NOTES: the formula for an ellipse is (x^2/a^2)+(y^2/b^2)=1
  //        when we calculate the ellipse, you can check if (x^2/a^2)+(y^2/b^2)<=1
  //        for fill, as all point points on and within fall into this formula.
  //        otherwhise you can check for (x^2/a^2)+(y^2/b^2)=1, for only then edge

  if (fill_type == FT_NO_FILL) {
    return DRAW_ellipse_no_fill(this, x, y, a, b);
  }

  int x0 = x - a;
  int y0 = y - b;

  int a2 = a*a;
  int b2 = b*b;

  for (int x1 = i_clamp(x0, 0, this->cols); x1 < 2*a; ++x1) {
    for (int y1 = i_clamp(y0, 0, this->rows); y1 < 2*b; ++y1) {
      float left = (x1*x1)/a2;
      float right = (y1*y1)/b2;
      float p = (left + right);
      if (p <= 1) {
        CANVAS_GET_PIXEL(*this, x1, y1) = color;
      }
    }
  }

  return 1;
}

int DRAW_circle(Canvas *this, int x, int y, int r) {
  // NOTE: just call the ellipse function, but with r in both slots
  return DRAW_ellipse(this, x, y, r, r);
}

// NOTE: using the Bresenhams line algorithm to draw the line
// LINK: https://en.wikipedia.org/wiki/Bresenham%27s_line_algorithm
int DRAW_line(Canvas *this, int x1, int y1, int x2, int y2) {
  x1 = i_clamp(x1, 0, this->cols);
  x2 = i_clamp(x2, 0, this->cols);
  y1 = i_clamp(y1, 0, this->rows);
  y2 = i_clamp(y2, 0, this->rows);

  if (x1 > x2) {
    SWAP(int, x1, x2);
    SWAP(int, y1, y1);
  }

  int dx = x2 - x1;
  int sx = dx > 0 ? 1 : -1;
  if (dx < 0)
    dx *= -1;

  int dy = y2 - y1;
  int sy = dy > 0 ? 1 : -1;
  if (dy > 0)
    dy *= -1;

  int error = dx + dy;

  int x = x1, y = y1;

  // NOTE: Draws the line, using magic

  while (1) {
    CANVAS_GET_PIXEL(*this, x, y) = color;
    if (x == x2 && y == y2) break;
    int e2 = 2 * error;
    if (e2 >= dy) {
      if (x == x2) break;
      error += dy;
      x += sx;
    }
    if (e2 <= dx) {
      if (y == y2) break;
      error += dx;
      y += sy;
    }
  }

  return 1;
}

static int DRAW_line_from_points(Canvas *this, Point *start, Point *end) {
  return DRAW_line(this, start->x, start->y, end->x, end->y);
}

int DRAW_rect(Canvas *this, int x, int y, int w, int h) {
  Normalized_Rect nr = {0};

  if (!CANVAS_normalize_rect(x, y, w, h, this, &nr)) return 0;

  return DRAW_line(this, x,   y,   x,   y+h) &&
         DRAW_line(this, x,   y,   x+w, y) &&
         DRAW_line(this, x+w, y,   x+w, y+h) &&
         DRAW_line(this, x,   y+h, x+w, y+h);
}

static int polygon_started = 0;
static Canvas *target = NULL;
static Point *points = NULL;
static int point_ptr = 0;

#ifndef POLYGON_MAX_POINTS
#define POLYGON_MAX_POINTS 32
#endif // POLYGON_MAX_POINTS

void DRAW_start_polygon(Canvas *this) {
  polygon_started = 1;
  points = malloc(sizeof(Point) * POLYGON_MAX_POINTS);
  target = this;
}

void DRAW_polygon_line_start(int x, int y) {
  points[point_ptr++] = POINT_new(x, y);
}

int DRAW_polygon_line(int x, int y) {
  if (point_ptr+1 > POLYGON_MAX_POINTS) {
    printf("you have reach the limit of your allowed polygons");
    return 0;
  }

  points[point_ptr++] = POINT_new(x, y);
  return DRAW_line_from_points(target, &points[point_ptr-2], &points[point_ptr-1]);
}

// TODO: change this to remove the actual line
void DRAW_polygon_pop(void) {
  point_ptr--;
}

// TODO: change this to remove the entire thing
void DRAW_polygon_clear(void) {
  point_ptr = 0;
}

void DRAW_end_plygon(void) {
  target = NULL;
  polygon_started = 0;
  free(points);
  points = NULL;
}

#endif // _CANVAS_DRAW_IMPLIMENTATION

