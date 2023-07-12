#include <stdio.h>

#include "./graphics/graphics.h"
#include "./cli_render/cli_render.h"

#define WIDTH 100
#define HEIGHT 50

int main(int argc, char** argv) {

 Canvas *c = CANVAS_create_canvas(WIDTH, HEIGHT);

  DRAW_set_color(0x00000001);
  DRAW_set_fill(FT_FILL);

  DRAW_line(c, 0, 0, WIDTH, HEIGHT);

  CANVAS_print(c);

  return 0;
}

