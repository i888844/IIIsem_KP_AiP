#include "stdio.h"
#include "stdlib.h"
#include "conio.h"
#include "math.h"
#include "time.h"
#include "windows.h"
#include "wingdi.h"
#include "locale.h"

#pragma warning(disable: 4996)

#define ESC 27
#define ENTER 13
#define DELTA 50

typedef struct
{
    int x;
    int y;
} dot;

HWND hWnd = GetConsoleWindow();
HDC hDC = GetDC(hWnd);
RECT Rect;
HBRUSH hBrush;
HBRUSH hOldBrush;
HBRUSH hBrushWhite = CreateSolidBrush(RGB(255, 255, 255));
HPEN hPenBlack = CreatePen(PS_SOLID, 5, RGB(0, 0, 0));
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
HFONT hFont;
HFONT hOldFont;
LOGFONT Lf = { 0 };

bool is_square_and_sides_not_zero(dot* square_dots)
{
    bool result = false;
    int left_side = sqrt(pow(square_dots[3].x - square_dots[0].x, 2) + pow(square_dots[3].y - square_dots[0].y, 2));
    int right_side = sqrt(pow(square_dots[2].x - square_dots[1].x, 2) + pow(square_dots[2].y - square_dots[1].y, 2));
    int top_side = sqrt(pow(square_dots[1].x - square_dots[0].x, 2) + pow(square_dots[1].y - square_dots[0].y, 2));
    int bottom_side = sqrt(pow(square_dots[2].x - square_dots[3].x, 2) + pow(square_dots[2].y - square_dots[3].y, 2));
    if (left_side != 0 && left_side == right_side && top_side != 0 && top_side == bottom_side)
    {
        result = true;
    }
    return result;
}

bool sides_parallel_to_axes(dot* square_dots)
{
    bool result = false;
    if (square_dots[0].x == square_dots[3].x && square_dots[1].x == square_dots[2].x && square_dots[0].y == square_dots[1].y && square_dots[3].y == square_dots[2].y)
    {
        result = true;
    }
    return result;
}

void create_dots_rand(dot* dots)
{
    for (int i = 0; i < 10; i++)
    {
        dots[i].x = rand() % 1001 - 500;
        dots[i].y = rand() % 1001 - 500;
    }
}

void create_dots_from_keyboard(dot* dots)
{
    printf("������� �����:\n");
    for (int i = 0; i < 10; i++)
    {
        printf("������� X ��� ����� �%i: ", i + 1);
        scanf_s("%i", &dots[i].x);
        while (dots[i].x < -500 || dots[i].x > 500)
        {
            printf("[������]: ���������� ����� ����� ���� �� -500 �� 500 ������������. ������� X ��� ����� �%i: ", i + 1);
            scanf_s("%i", &dots[i].x);
        }
        printf("������� Y ��� ����� �%i: ", i + 1);
        scanf_s("%i", &dots[i].y);
        while (dots[i].y < -500 || dots[i].y > 500)
        {
            printf("[������]: ���������� ����� ����� ���� �� -500 �� 500 ������������. ������� Y ��� ����� �%i: ", i + 1);
            scanf_s("%i", &dots[i].y);
        }
    }
}

void create_dots_from_file(dot* dots, const char* filename)
{
    FILE* file = fopen(filename, "r");
    if (file == NULL)
    {
        printf("[������]: �� ������� ������� ����.\n");
        exit(1);
    }
    int number = 0;
    for (int i = 0; i < 20; i++)
    {
        number = 0;
        
        if (fscanf(file, "%i", &number) == 1 && (number >= -500 && number <= 500))
        {
            if (i % 2)
            {
                dots[i].x = number;
            }
            else
            {
                dots[i].y = number;
            }
        }
        else
        {
            if (i % 2)
            {
                dots[i].x = rand() % 1001 - 500;
            }
            else
            {
                dots[i].y = rand() % 1001 - 500;
            }
        }
    }
}

bool in_square(dot* square_dots, dot* dot)
{
    bool result = false;
    if (dot->x >= square_dots[0].x && dot->x <= square_dots[2].x && dot->y <= square_dots[0].y && dot->y >= square_dots[2].y)
    {
        result = true;
    }
    return result;
}

void print_line_in_axes(int x_line_start, int y_line_start, int x_line_end, int y_line_end, int number_sign_coord, int x_text, int y_text)
{
    int coord = 0;
    CHAR S[10];
    MoveToEx(hDC, x_line_start, y_line_start, NULL);
    LineTo(hDC, x_line_end, y_line_end);
    coord += DELTA;
    sprintf_s(S, "%i", number_sign_coord * coord);
    TextOut(hDC, x_text, y_text, (LPCWSTR)S, strlen(S));
}

void print_axes()
{
    int i = 0;
    int horizontal_center = (Rect.right - Rect.left) / 2 + 500;
    int vertical_center = Rect.bottom / 2;
    SelectObject(hDC, hBrushWhite);
    Rectangle(hDC, Rect.left, Rect.top, Rect.right, Rect.bottom);
    SelectObject(hDC, hPenBlack);
    MoveToEx(hDC, horizontal_center, Rect.top, NULL);
    LineTo(hDC, horizontal_center, Rect.bottom);
    TextOut(hDC, Rect.right - 16, vertical_center, (LPCWSTR)"X", strlen("X"));
    TextOut(hDC, horizontal_center, vertical_center, (LPCWSTR)"0", strlen("0"));
    MoveToEx(hDC, 0, vertical_center, NULL);
    LineTo(hDC, Rect.right, vertical_center);
    TextOut(hDC, horizontal_center, Rect.top, (LPCWSTR)"Y", strlen("Y"));
    SelectObject(hDC, hPenGrey);
    for (i = horizontal_center + DELTA; i < Rect.right; i += DELTA)
    {
        print_line_in_axes(i, Rect.top, i, Rect.bottom, 1, i, vertical_center);
    }
    for (i = horizontal_center - DELTA; i > Rect.left; i -= DELTA)
    {
        print_line_in_axes(i, Rect.top, i, Rect.bottom, -1, i, vertical_center);
    }
    for (i = vertical_center - DELTA; i > Rect.top; i -= DELTA)
    {
        print_line_in_axes(Rect.left, i, Rect.right, i, 1, horizontal_center, i);
    }
    for (i = vertical_center + DELTA; i < Rect.bottom; i += DELTA)
    {
        print_line_in_axes(Rect.left, i, Rect.right, i, -1, horizontal_center, i);
    }
}

void print_square(dot* square_dots)
{
    int horizontal_center = (Rect.right - Rect.left) / 2 + 500;
    int vertical_center = Rect.bottom / 2;
    SelectObject(hDC, hPenRed);
    MoveToEx(hDC, horizontal_center + square_dots[0].x, vertical_center - square_dots[0].y, NULL);
    LineTo(hDC, horizontal_center + square_dots[1].x, vertical_center - square_dots[1].y);
    LineTo(hDC, horizontal_center + square_dots[2].x, vertical_center - square_dots[2].y);
    LineTo(hDC, horizontal_center + square_dots[3].x, vertical_center - square_dots[3].y);
    LineTo(hDC, horizontal_center + square_dots[0].x, vertical_center - square_dots[0].y);
}

void print_dots(dot* square_dots, dot* dots, HPEN dots_color_in_square, HPEN dots_color_out_square)
{
    int horizontal_center = (Rect.right - Rect.left) / 2 + 500;
    int vertical_center = Rect.bottom / 2;
    for (int i = 0; i < 10; i++)
    {
        if (in_square(square_dots, &dots[i]))
        {
            SelectObject(hDC, dots_color_in_square);
        }
        else
        {
            SelectObject(hDC, dots_color_out_square);
        }
        Ellipse(hDC, horizontal_center + (dots[i].x - 5), vertical_center - (dots[i].y), horizontal_center + (dots[i].x + 5), vertical_center - (dots[i].y + 5));
    }
}

int solving_geometric_tasks()
{
    Lf.lfHeight = 16;
    Lf.lfWeight = 900;
    Lf.lfWidth = 8;
    Lf.lfCharSet = RUSSIAN_CHARSET;
    strcpy((char*)Lf.lfFaceName, "Times New Roman");
    hFont = CreateFontIndirect(&Lf);
    hOldFont = (HFONT)SelectObject(hDC, hFont);
    SetTextColor(hDC, RGB(0, 0, 0));
    SetBkColor(hDC, RGB(255, 255, 255));
    GetClientRect(hWnd, &Rect);
    Rect.right += 500;
    Rect.left += 500;
    dot square_dots[4];
    int i = 0;
    printf("������� ����� ����� ��������:\n");
    for (i = 0; i < 4; i++)
    {
        printf("������� X ��� ����� �%i: ", i + 1);
        scanf_s("%i", &square_dots[i].x);
        while (square_dots[i].x < -500 || square_dots[i].x > 500)
        {
            printf("[������]: ���������� ����� ����� ���� �� -500 �� 500 ������������. ������� X ��� ����� �%i: ", i + 1);
            scanf_s("%i", &square_dots[i].x);
        }
        printf("������� Y ��� ����� �%i: ", i + 1);
        scanf_s("%i", &square_dots[i].y);
        while (square_dots[i].y < -500 || square_dots[i].y > 500)
        {
            printf("[������]: ���������� ����� ����� ���� �� -500 �� 500 ������������. ������� Y ��� ����� �%i: ", i + 1);
            scanf_s("%i", &square_dots[i].y);
        }
    }
    while (!is_square_and_sides_not_zero(&square_dots[0]) || !sides_parallel_to_axes(&square_dots[0]))
    {
        printf("[������]: �������� ���������� �� �������� �������, ������� �������� ����������� ����. ��������� �������:\n");
        for (i = 0; i < 4; i++)
        {
            printf("������� X ��� ����� �%i: ", i + 1);
            scanf_s("%i", &square_dots[i].x);
            while (square_dots[i].x < -500 || square_dots[i].x > 500)
            {
                printf("[������]: ���������� ����� ����� ���� �� -500 �� 500 ������������. ������� X ��� ����� �%i: ", i + 1);
                scanf_s("%i", &square_dots[i].x);
            }
            printf("������� Y ��� ����� �%i: ", i + 1);
            scanf_s("%i", &square_dots[i].y);
            while (square_dots[i].y < -500 || square_dots[i].y > 500)
            {
                printf("[������]: ���������� ����� ����� ���� �� -500 �� 500 ������������. ������� Y ��� ����� �%i: ", i + 1);
                scanf_s("%i", &square_dots[i].y);
            }
        }
    }
    int cmd = 0;
    dot dots[10];
    printf("�������� ������� ������������ �����:\n");
    printf("1. ������������ ����� ��������� �������.\n");
    printf("2. ������������ ����� ������ � ����������.\n");
    printf("3. ������������ ����� ������� �� �����.\n");
    printf("0. ��������� ������ ���������.\n");
    printf("������� ����� ��������: ");
    scanf_s("%i", &cmd);
    while (cmd < 0 || cmd > 3)
    {
        printf("[������]: ������ �������� ����� ��������. ������� ����� ��������: ");
        scanf_s("%i", &cmd);
    }
    switch (cmd)
    {
        case 0:
        {
            return 0;
            break;
        }
        case 1:
        {
            create_dots_rand(&dots[0]);
            break;
        }
        case 2:
        {
            create_dots_from_keyboard(&dots[0]);
            break;
        }
        case 3:
        {
            char filename[256];
            printf("������� �������� ����� � �������� (������: filename.txt): ");
            scanf_s("%255s", &filename, sizeof(filename));
            create_dots_from_file(&dots[0], filename);
            break;
        }
    }
    for (i = 0; i < 10; i++)
    {
        if (in_square(&square_dots[0], &dots[i]))
        {
            printf("����� �%i - ������ ��������:\n", i + 1);
        }
        else
        {
            printf("����� �%i - ��� ��������:\n", i + 1);
        }
        printf("X: %i\n", dots[i].x);
        printf("Y: %i\n\n", dots[i].y);
    }
    int key = 0;
    HPEN dots_color_in_square = hPenGreen;
    HPEN dots_color_out_square = hPenBlue;
    do
    {
        print_axes();
        print_square(&square_dots[0]);
        print_dots(&square_dots[0], &dots[0], dots_color_in_square, dots_color_out_square);
        key = _getch();
        if (key == ENTER)
        {
            do
            {
                i = rand() % 7;
                dots_color_in_square = hPenColors[i];
                i = rand() % 7;
                dots_color_out_square = hPenColors[i];
            } while (dots_color_in_square == dots_color_out_square);
        }
    } while (key != ESC);
	return 0;
}