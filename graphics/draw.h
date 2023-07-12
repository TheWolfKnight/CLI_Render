
#include "./canvas.h"

#ifndef _CANVAS_DRAW_DEFINITION
#define _CANVAS_DRAW_DEFINITION

typedef enum {
  FT_FILL = 0,
  FT_NO_FILL,
} FillType;

void DRAW_set_fill(FillType ft);
void DRAW_set_color(uint32_t cl);

int DRAW_ellipse(Canvas *this, int x, int y, int a, int b);
int DRAW_circle(Canvas *this, int x, int y, int r);
int DRAW_rect(Canvas *this, int x, int y, int w, int h);
int DRAW_line(Canvas *this, int x1, int y1, int x2, int y2);

void DRAW_start_polygon(Canvas *this);
void DRAW_polygon_line_start(int x, int y);
int DRAW_polygon_line(int x, int y);
void DRAW_polygon_pop(void);
void DRAW_polygon_clear(void);
void DRAW_end_polygon(void);

#endif // _CANVAS_DRAW_DEFINITION
