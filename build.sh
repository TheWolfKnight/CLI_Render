
CLI_FILES="cli_render/_cursor_impls/_linux_cursor.c cli_render/_screen_impls/_linux_screen.c"
GRAP_FILES="graphics/canvas.c graphics/draw.c graphics/point.c"
MAIN_FILES="main.c"
FLAGS="-Wall -o a.o -g"

gcc $FLAGS $CLI_FILES $GRAP_FILES $MAIN_FILES
