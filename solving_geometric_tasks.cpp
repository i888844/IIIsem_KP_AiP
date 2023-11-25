#include "common.h"

RECT TRect;

typedef struct
{
    int x;
    int y;
} dot;

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
    printf("Введите точки:\n");
    for (int i = 0; i < 10; i++)
    {
        printf("Введите X для точки №%i: ", i + 1);
        scanf_s("%i", &dots[i].x);
        while (dots[i].x < -500 || dots[i].x > 500)
        {
            printf("[Ошибка]: координаты точки могут быть от -500 до 500 включительно. Введите X для точки №%i: ", i + 1);
            scanf_s("%i", &dots[i].x);
        }
        printf("Введите Y для точки №%i: ", i + 1);
        scanf_s("%i", &dots[i].y);
        while (dots[i].y < -500 || dots[i].y > 500)
        {
            printf("[Ошибка]: координаты точки могут быть от -500 до 500 включительно. Введите Y для точки №%i: ", i + 1);
            scanf_s("%i", &dots[i].y);
        }
    }
}

void create_dots_from_file(dot* dots, const char* filename)
{
    FILE* file = fopen(filename, "r");
    if (file == NULL)
    {
        printf("[Ошибка]: Не удалось открыть файл.\n");
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

void print_line_in_axes(int x_line_start, int y_line_start, int x_line_end, int y_line_end, int number_sign_coord, int x_text, int y_text, int coord)
{
    CHAR S[10];
    MoveToEx(hDC, x_line_start, y_line_start, NULL);
    LineTo(hDC, x_line_end, y_line_end);
    sprintf_s(S, "%i", number_sign_coord * coord);
    TextOut(hDC, x_text, y_text, (LPCSTR)S, strlen(S));
}

void print_axes()
{
    int i = 0;
    int horizontal_center = (TRect.right - TRect.left) / 2 + 525;
    int vertical_center = TRect.bottom / 2;
    int coord = 0;
    SelectObject(hDC, hBrushWhite);
    Rectangle(hDC, TRect.left, TRect.top, TRect.right, TRect.bottom);
    SelectObject(hDC, hPenBlack);
    MoveToEx(hDC, horizontal_center, TRect.top, NULL);
    LineTo(hDC, horizontal_center, TRect.bottom);
    TextOut(hDC, TRect.right - 16, vertical_center, (LPCSTR)"X", strlen("X") + 1);
    TextOut(hDC, horizontal_center, vertical_center, (LPCSTR)"0", strlen("0") + 1);
    MoveToEx(hDC, 0, vertical_center, NULL);
    LineTo(hDC, TRect.right, vertical_center);
    TextOut(hDC, horizontal_center, TRect.top, (LPCSTR)"Y", strlen("Y") + 1);
    SelectObject(hDC, hPenGrey);
    for (i = horizontal_center + DELTA; i < TRect.right; i += DELTA)
    {
        coord += DELTA;
        print_line_in_axes(i, TRect.top, i, TRect.bottom, 1, i, vertical_center, coord);
    }
    coord = 0;
    for (i = horizontal_center - DELTA; i > TRect.left; i -= DELTA)
    {
        coord += DELTA;
        print_line_in_axes(i, TRect.top, i, TRect.bottom, -1, i, vertical_center, coord);
    }
    coord = 0;
    for (i = vertical_center - DELTA; i > TRect.top; i -= DELTA)
    {
        coord += DELTA;
        print_line_in_axes(TRect.left, i, TRect.right, i, 1, horizontal_center, i, coord);
    }
    coord = 0;
    for (i = vertical_center + DELTA; i < TRect.bottom; i += DELTA)
    {
        coord += DELTA;
        print_line_in_axes(TRect.left, i, TRect.right, i, -1, horizontal_center, i, coord);
    }
}

void print_square(dot* square_dots)
{
    int horizontal_center = (TRect.right - TRect.left) / 2 + 525;
    int vertical_center = TRect.bottom / 2;
    SelectObject(hDC, hPenRed);
    MoveToEx(hDC, horizontal_center + square_dots[0].x, vertical_center - square_dots[0].y, NULL);
    LineTo(hDC, horizontal_center + square_dots[1].x, vertical_center - square_dots[1].y);
    LineTo(hDC, horizontal_center + square_dots[2].x, vertical_center - square_dots[2].y);
    LineTo(hDC, horizontal_center + square_dots[3].x, vertical_center - square_dots[3].y);
    LineTo(hDC, horizontal_center + square_dots[0].x, vertical_center - square_dots[0].y);
}

void print_dots(dot* square_dots, dot* dots, HPEN dots_color_in_square, HPEN dots_color_out_square)
{
    int horizontal_center = (TRect.right - TRect.left) / 2 + 525;
    int vertical_center = TRect.bottom / 2;
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

int solving_geometric_tasks(int mode)
{
    system("CLS");
    TRect = Rect;
    TRect.left = 525;
    TRect.right = 1725;
    dot square_dots[4];
    int i = 0;
    printf("Введите точки углов квадрата:\n");
    for (i = 0; i < 4; i++)
    {
        printf("Введите X для точки №%i: ", i + 1);
        scanf_s("%i", &square_dots[i].x);
        while (square_dots[i].x < -500 || square_dots[i].x > 500)
        {
            printf("[Ошибка]: координаты точки могут быть от -500 до 500 включительно. Введите X для точки №%i: ", i + 1);
            scanf_s("%i", &square_dots[i].x);
        }
        printf("Введите Y для точки №%i: ", i + 1);
        scanf_s("%i", &square_dots[i].y);
        while (square_dots[i].y < -500 || square_dots[i].y > 500)
        {
            printf("[Ошибка]: координаты точки могут быть от -500 до 500 включительно. Введите Y для точки №%i: ", i + 1);
            scanf_s("%i", &square_dots[i].y);
        }
    }
    while (!is_square_and_sides_not_zero(&square_dots[0]) || !sides_parallel_to_axes(&square_dots[0]))
    {
        printf("[Ошибка]: введённые координаты не образуют квадрат, стороны которого параллельны осям. Повторите попытку:\n");
        for (i = 0; i < 4; i++)
        {
            printf("Введите X для точки №%i: ", i + 1);
            scanf_s("%i", &square_dots[i].x);
            while (square_dots[i].x < -500 || square_dots[i].x > 500)
            {
                printf("[Ошибка]: координаты точки могут быть от -500 до 500 включительно. Введите X для точки №%i: ", i + 1);
                scanf_s("%i", &square_dots[i].x);
            }
            printf("Введите Y для точки №%i: ", i + 1);
            scanf_s("%i", &square_dots[i].y);
            while (square_dots[i].y < -500 || square_dots[i].y > 500)
            {
                printf("[Ошибка]: координаты точки могут быть от -500 до 500 включительно. Введите Y для точки №%i: ", i + 1);
                scanf_s("%i", &square_dots[i].y);
            }
        }
    }
    int cmd = 0;
    dot dots[10];
    switch (mode)
    {
	    case WITH_FILE_INPUT:
	    {
	        char filename[256];
	        printf("Введите путь к файлу (пример: D:\\Documents\\filename.txt): ");
	        scanf_s("%255s", &filename, sizeof(filename));
            create_dots_from_file(&dots[0], filename);
	        break;
	    }
	    case WITH_RANDOM_GENERATION:
	    {
            create_dots_rand(&dots[0]);
	        break;
	    }
	    case WITH_KEYBOARD_INPUT:
	    {
            create_dots_from_keyboard(&dots[0]);
	        break;
	    }
    }
    for (i = 0; i < 10; i++)
    {
        if (in_square(&square_dots[0], &dots[i]))
        {
            printf("Точка №%i - внутри квадрата:\n", i + 1);
        }
        else
        {
            printf("Точка №%i - вне квадрата:\n", i + 1);
        }
        printf("X: %i\n", dots[i].x);
        printf("Y: %i\n\n", dots[i].y);
    }
    printf("\nДаважды нажмите ESC, чтоб вернуться в меню...");
    int tkey = 0;
    HPEN dots_color_in_square = hPenGreen;
    HPEN dots_color_out_square = hPenBlue;
    SetTextColor(hDC, RGB(0, 0, 0));
    SetBkColor(hDC, RGB(255, 255, 255));
    (HFONT)SelectObject(hDC, hFontGraph);
    do
    {
        print_axes();
        print_square(&square_dots[0]);
        print_dots(&square_dots[0], &dots[0], dots_color_in_square, dots_color_out_square);
        tkey = _getch();
        if (tkey != ESC)
        {
            do
            {
                i = rand() % 7;
                dots_color_in_square = hPenColors[i];
                i = rand() % 7;
                dots_color_out_square = hPenColors[i];
            } while (dots_color_in_square == dots_color_out_square);
        }
    } while (tkey != ESC);
    _getch();
    SetTextColor(hDC, RGB(0, 0, 0));
    SetBkColor(hDC, RGB(255, 255, 255));
    system("CLS");
	return 0;
}