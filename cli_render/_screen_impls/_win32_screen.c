
#include <windows.h>

#include "./screen.h"

#ifndef _CLI_SCREEN_WIN32_IMPLIMENTATION
#define _CLI_SCREEN_WIN32_IMPLIMENTATION

int get_columns(void) {
  CONSOLE_SCREEN_BUFFER_INFO csbi;
  int columns;

  GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi);
  columns = csbi.srWindow.Right - csbi.srWindow.Left + 1;

  return columns;
}

int get_rows(void) {
  CONSOLE_SCREEN_BUFFER_INFO csbi;
  int rows;

  GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi);
  rows = csbi.srWindow.Bottom - csbi.srWindow.Top + 1;

  return rows;
}

#endif // _CLI_SCREEN_WIN32_IMPLIMENTATION

