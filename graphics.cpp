//graphics.cpp

// This is a personal academic project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++, C#, and Java: https://pvs-studio.com

#include "common.h"
#include "graphics.h"

HWND hWnd = GetConsoleWindow();
HDC hDC = GetDC(hWnd);
HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
RECT Rect;
RECT TRect;
HBRUSH hBrushWhite = CreateSolidBrush(RGB(255, 255, 255));
HBRUSH hBrushBIOSBlue = CreateSolidBrush(RGB(0, 0, 207));
HBRUSH hBrushBIOSLightBlue = CreateSolidBrush(RGB(54, 54, 255));
HPEN hPenBlack = CreatePen(PS_SOLID, 5, RGB(0, 0, 0));
HPEN hPenWhite = CreatePen(PS_SOLID, 5, RGB(255, 255, 255));
HPEN hPenRed = CreatePen(PS_SOLID, 5, RGB(255, 0, 0));
HPEN hPenGrey = CreatePen(PS_SOLID, 3, RGB(71, 74, 81));
HPEN hPenGreen = CreatePen(PS_SOLID, 5, RGB(0, 255, 0));
HPEN hPenBlue = CreatePen(PS_SOLID, 5, RGB(0, 0, 255));
HPEN hPenCyan = CreatePen(PS_SOLID, 5, RGB(0, 255, 255));
HPEN hPenPurple = CreatePen(PS_SOLID, 5, RGB(128, 0, 128));
HPEN hPenOrange = CreatePen(PS_SOLID, 5, RGB(255, 165, 0));
HPEN hPenPink = CreatePen(PS_SOLID, 5, RGB(255, 192, 203));
HPEN hPenBrown = CreatePen(PS_SOLID, 5, RGB(139, 69, 19));
HPEN hPenColors[7] = { hPenGreen, hPenBlue, hPenCyan, hPenPurple, hPenOrange, hPenPink, hPenBrown };
HFONT hFontGraph;
HFONT hFontMenuName;
HFONT hFontMenuStrings;
LOGFONT LfGraph = {
    .lfHeight = 16,
    .lfWidth = 8,
    .lfWeight = 900,
    .lfCharSet = RUSSIAN_CHARSET
};
LOGFONT LfMenuName = {
    .lfHeight = 64,
    .lfWidth = 32,
    .lfWeight = 900,
    .lfCharSet = RUSSIAN_CHARSET
};
LOGFONT LfMenuStrings = {
    .lfHeight = 32,
    .lfWidth = 16,
    .lfWeight = 900,
    .lfCharSet = RUSSIAN_CHARSET
};