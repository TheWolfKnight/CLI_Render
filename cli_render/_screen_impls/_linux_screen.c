
#include <sys/ioctl.h>

#include "./screen.h"

#ifndef _CLI_SCREEN_LINUX_IMPLIMENTATION
#define _CLI_SCREEN_LINUX_IMPLIMENTATION

int get_columns(void) {
  struct winsize w;
  ioctl(0, TIOCGWINSZ, &w);
  return w.ws_col;
}

int get_rows(void) {
  struct winsize w;
  ioctl(0, TIOCGWINSZ, &w);
  return w.ws_row;
}

#endif // _CLI_SCREEN_LINUX_IMPLIMENTATION

