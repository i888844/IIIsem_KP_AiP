//graphics.h

#pragma once;
#ifndef GRAPHICS
#define GRAPHICS

extern HWND hWnd;
extern HDC hDC;
extern RECT Rect;
extern RECT TRect;
extern HBRUSH hBrushWhite;
extern HBRUSH hBrushBIOSBlue;
extern HBRUSH hBrushBIOSLightBlue;
extern HPEN hPenBlack;
extern HPEN hPenWhite;
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
extern LOGFONT LfGraph;
extern LOGFONT LfMenuName;
extern LOGFONT LfMenuStrings;

#endif