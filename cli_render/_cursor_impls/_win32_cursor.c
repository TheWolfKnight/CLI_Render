
#include <windows.h>

#include "./cursor.h"

#ifndef _CLI_CURSOR_IMPLIMENTATION
#define _CLI_CURSOR_IMPLIMENTATION

void move_cursor(int x, int y) {
  HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
  COORD pos = { x, y };
  SetConsoleCursorPosition(hConsole, pos);
  return;
}

void shift_cursor(int x, int y) {
  return;
}

#endif // _CLI_CURSOR_IMPLIMENTATION
