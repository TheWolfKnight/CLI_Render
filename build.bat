@echo off

set CLI_FILES=cli_render\_cursor_impls\_win32_cursor.c cli_render\_screen_impls\_win32_screen.c
set GRAP_FILES=graphics\canvas.c graphics\draw.c graphics\point.c
set MAIN_FILES=main.c
set FLAGS=-Wall -o a.exe

call gcc %FLAGS% %MAIN_FILES% %GRAP_FILES% %CLI_FILES%

