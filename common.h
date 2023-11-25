//common.h
#pragma once

#define _CRT_SECURE_NO_WARNINGS
#define ANSI_COLOR_RED "\x1b[31m"
#define ANSI_COLOR_RESET "\x1b[0m"
#define ESC 27
#define ENTER 13
#define ARROW_UP 72
#define ARROW_DOWN 80
#define ARROW_LEFT 75
#define ARROW_RIGHT 77
#define DELTA 50
#define WITH_FILE_INPUT 1
#define WITH_RANDOM_GENERATION 2
#define WITH_KEYBOARD_INPUT 3

#include "stdio.h"
#include "stdlib.h"
#include "conio.h"
#include "math.h"
#include "time.h"
#include "windows.h"
#include "wingdi.h"
#include "locale.h"

extern HWND hWnd;
extern HDC hDC;
extern RECT Rect;
extern HBRUSH hBrush;
extern HBRUSH hOldBrush;
extern HBRUSH hBrushWhite;
extern HPEN hPenBlack;
extern HPEN hPenRed;
extern HPEN hPenGrey;
extern HPEN hPenGreen;
extern HPEN hPenBlue;
extern HPEN hPenCyan;
extern HPEN hPenPurple;
extern HPEN hPenOrange;
extern HPEN hPenPink;
extern HPEN hPenBrown;
extern HPEN hPenColors[7];
extern HFONT hFont;
extern HFONT hOldFont;
extern HFONT hFontGraph;
extern HFONT hFontMenuName;
extern HFONT hFontMenuStrings;
extern LOGFONT Lf;