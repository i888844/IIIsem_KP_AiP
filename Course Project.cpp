//Course Project.cpp
#include <iostream>
#include "common.h"
#include "matrix_processing.cpp"
#include "solving_geometric_tasks.cpp"
#include "sorting_tasks.cpp"

HWND hWnd = GetConsoleWindow();
HDC hDC = GetDC(hWnd);
HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
RECT Rect;
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

void print_button(int left, int top, int right, int bottom, const char* string)
{
    MoveToEx(hDC, Rect.left + left, Rect.top + top, NULL);
    LineTo(hDC, Rect.right - right, Rect.top + top);
    LineTo(hDC, Rect.right - right, Rect.top + bottom);
    LineTo(hDC, Rect.left + left, Rect.top + bottom);
    LineTo(hDC, Rect.left + left, Rect.top + top);
    TextOut(hDC, Rect.left + left + 8, Rect.top + top + 4, (LPCSTR)string, strlen(string) + 1);
}

void print_button_selected(int left, int top, int right, int bottom, const char* string)
{
    (HBRUSH)SelectObject(hDC, hBrushWhite);
    SetTextColor(hDC, RGB(0, 0, 0));
    SetBkColor(hDC, RGB(255, 255, 255));
    Rectangle(hDC, Rect.left + left, Rect.top + top, Rect.right - right, Rect.top + bottom);
    TextOut(hDC, Rect.left + left + 8, Rect.top + top + 4, (LPCSTR)string, strlen(string) + 1);
    (HPEN)SelectObject(hDC, hPenWhite);
    SetTextColor(hDC, RGB(255, 255, 255));
    SetBkColor(hDC, RGB(0, 0, 207));
}

void print_menu(int main_index, int sub_index)
{
    int deductible = 0;
    int horizontal_center = Rect.right / 2;
    int vertical_center = Rect.bottom / 2;
    (HPEN)SelectObject(hDC, hPenWhite);
    SetTextColor(hDC, RGB(0, 0, 0));
    SetBkColor(hDC, RGB(255, 255, 255));
    (HBRUSH)SelectObject(hDC, hBrushBIOSLightBlue);
    Rectangle(hDC, Rect.left, Rect.top, Rect.right, Rect.bottom);
    (HBRUSH)SelectObject(hDC, hBrushBIOSBlue);
    Rectangle(hDC, Rect.left + 100, Rect.top + 50, Rect.right - 100, Rect.bottom - 50);
    (HPEN)SelectObject(hDC, hPenWhite);
    MoveToEx(hDC, Rect.left + 100, Rect.top + 50, NULL);
    LineTo(hDC, Rect.right - 100, Rect.top + 50);
    LineTo(hDC, Rect.right - 100, Rect.bottom - 50);
    LineTo(hDC, Rect.left + 100, Rect.bottom - 50);
    LineTo(hDC, Rect.left + 100, Rect.top + 50);
    (HFONT)SelectObject(hDC, hFontMenuName);
    TextOut(hDC, horizontal_center - 128, Rect.top + 50, (LPCSTR)"МЕНЮ", strlen("МЕНЮ"));
    MoveToEx(hDC, horizontal_center - 128, Rect.top + 50, NULL);
    LineTo(hDC, horizontal_center - 128, Rect.top + 114);
    LineTo(hDC, horizontal_center + 128, Rect.top + 114);
    LineTo(hDC, horizontal_center + 128, Rect.top + 50);
    (HFONT)SelectObject(hDC, hFontMenuStrings);
    SetTextColor(hDC, RGB(255, 255, 255));
    SetBkColor(hDC, RGB(0, 0, 207));
    switch(main_index)
    {
		case 0:
	    {
            print_button_selected(300, 130, 300, 170, "Справка");
            switch(sub_index)
            {
				case 0:
	            {
                    deductible = 280;
                    break;
	            }
				case 1:
	            {
                    print_button_selected(364, 186, 300, 226, "Об управлении меню");
                    print_button(364, 242, 300, 282, "О курсовом проекте");
                    print_button(364, 298, 300, 338, "О задании №1 - Обработка матриц");
                    print_button(364, 354, 300, 394, "О задании №2 - Решение геометрических задач");
                    print_button(364, 410, 300, 450, "О задании №3 - Задачи сортировки");
                    break;
	            }
		        case 2:
				{
                    print_button(364, 186, 300, 226, "Об управлении меню");
                    print_button_selected(364, 242, 300, 282, "О курсовом проекте");
                    print_button(364, 298, 300, 338, "О задании №1 - Обработка матриц");
                    print_button(364, 354, 300, 394, "О задании №2 - Решение геометрических задач");
                    print_button(364, 410, 300, 450, "О задании №3 - Задачи сортировки");
                    break;
				}
                case 3:
                {
                    print_button(364, 186, 300, 226, "Об управлении меню");
                    print_button(364, 242, 300, 282, "О курсовом проекте");
                    print_button_selected(364, 298, 300, 338, "О задании №1 - Обработка матриц");
                    print_button(364, 354, 300, 394, "О задании №2 - Решение геометрических задач");
                    print_button(364, 410, 300, 450, "О задании №3 - Задачи сортировки");
                    break;
                }
                case 4:
                {
                    print_button(364, 186, 300, 226, "Об управлении меню");
                    print_button(364, 242, 300, 282, "О курсовом проекте");
                    print_button(364, 298, 300, 338, "О задании №1 - Обработка матриц");
                    print_button_selected(364, 354, 300, 394, "О задании №2 - Решение геометрических задач");
                    print_button(364, 410, 300, 450, "О задании №3 - Задачи сортировки");
                    break;
                }
                case 5:
                {
                    print_button(364, 186, 300, 226, "Об управлении меню");
                    print_button(364, 242, 300, 282, "О курсовом проекте");
                    print_button(364, 298, 300, 338, "О задании №1 - Обработка матриц");
                    print_button(364, 354, 300, 394, "О задании №2 - Решение геометрических задач");
                    print_button_selected(364, 410, 300, 450, "О задании №3 - Задачи сортировки");
                    break;
                }
            }
            print_button(300, 466 - deductible, 300, 506 - deductible, "Задание №1 - Обработка матриц");
            print_button(300, 522 - deductible, 300, 562 - deductible, "Задание №2 - Решение геометрических задач");
            print_button(300, 578 - deductible, 300, 618 - deductible, "Задание №3 - Задачи сортировки");
            print_button(300, 634 - deductible, 300, 674 - deductible, "Выход");
            break;
	    }
		case 1:
		{
			print_button(300, 130, 300, 170, "Справка");
            print_button_selected(300, 186, 300, 226, "Задание №1 - Обработка матриц");
            switch (sub_index)
            {
	            case 0:
	            {
	                deductible = 168;
	                break;
	            }
	            case 1:
	            {
	                print_button_selected(364, 242, 300, 282, "Запустить в режиме ручного ввода значений матрицы");
	                print_button(364, 298, 300, 338, "Запустить в режиме слуйной генерации значений матрицы");
	                print_button(364, 354, 300, 394, "Запустить в режиме считывания значений матрицы из файла");
	                break;
	            }
	            case 2:
	            {
                    print_button(364, 242, 300, 282, "Запустить в режиме ручного ввода значений матрицы");
                    print_button_selected(364, 298, 300, 338, "Запустить в режиме слуйной генерации значений матрицы");
                    print_button(364, 354, 300, 394, "Запустить в режиме считывания значений матрицы из файла");
	                break;
	            }
	            case 3:
	            {
                    print_button(364, 242, 300, 282, "Запустить в режиме ручного ввода значений матрицы");
                    print_button(364, 298, 300, 338, "Запустить в режиме слуйной генерации значений матрицы");
                    print_button_selected(364, 354, 300, 394, "Запустить в режиме считывания значений матрицы из файла");
	                break;
	            }
            }
            print_button(300, 410 - deductible, 300, 450 - deductible, "Задание №2 - Решение геометрических задач");
            print_button(300, 466 - deductible, 300, 506 - deductible, "Задание №3 - Задачи сортировки");
            print_button(300, 522 - deductible, 300, 562 - deductible, "Выход");
            break;
		}
        case 2:
        {
            print_button(300, 130, 300, 170, "Справка");
            print_button(300, 186, 300, 226, "Задание №1 - Обработка матриц");
            print_button_selected(300, 242, 300, 282, "Задание №2 - Решение геометрических задач");
            switch (sub_index)
            {
	            case 0:
	            {
	                deductible = 168;
	                break;
	            }
	            case 1:
	            {
                    print_button_selected(364, 298, 300, 338, "Запустить в режиме ручного ввода координат 10 точек");
                    print_button(364, 354, 300, 394, "Запустить в режиме слуйной генерации координат 10 точек");
                    print_button(364, 410, 300, 450, "Запустить в режиме считывания координат 10 точек из файла");
	                break;
	            }
	            case 2:
	            {
                    print_button(364, 298, 300, 338, "Запустить в режиме ручного ввода координат 10 точек");
                    print_button_selected(364, 354, 300, 394, "Запустить в режиме слуйной генерации координат 10 точек");
                    print_button(364, 410, 300, 450, "Запустить в режиме считывания координат 10 точек из файла");
	                break;
	            }
	            case 3:
	            {
                    print_button(364, 298, 300, 338, "Запустить в режиме ручного ввода координат 10 точек");
                    print_button(364, 354, 300, 394, "Запустить в режиме слуйной генерации координат 10 точек");
                    print_button_selected(364, 410, 300, 450, "Запустить в режиме считывания координат 10 точек из файла");
	                break;
	            }
            }
            print_button(300, 466 - deductible, 300, 506 - deductible, "Задание №3 - Задачи сортировки");
            print_button(300, 522 - deductible, 300, 562 - deductible, "Выход");
            break;
        }
        case 3:
        {
            print_button(300, 130, 300, 170, "Справка");
            print_button(300, 186, 300, 226, "Задание №1 - Обработка матриц");
            print_button(300, 242, 300, 282, "Задание №2 - Решение геометрических задач");
            print_button_selected(300, 298, 300, 338, "Задание №3 - Задачи сортировки");
            switch (sub_index)
            {
	            case 0:
	            {
	                deductible = 168;
	                break;
	            }
	            case 1:
	            {
	                print_button_selected(364, 354, 300, 394, "Запустить в режиме ручного ввода значений массива");
	                print_button(364, 410, 300, 450, "Запустить в режиме слуйной генерации значений массива");
	                print_button(364, 466, 300, 506, "Запустить в режиме считывания значений массива из файла");
	                break;
	            }
	            case 2:
	            {
                    print_button(364, 354, 300, 394, "Запустить в режиме ручного ввода значений массива");
                    print_button_selected(364, 410, 300, 450, "Запустить в режиме слуйной генерации значений массива");
                    print_button(364, 466, 300, 506, "Запустить в режиме считывания значений массива из файла");
	                break;
	            }
	            case 3:
	            {
                    print_button(364, 354, 300, 394, "Запустить в режиме ручного ввода значений массива");
                    print_button(364, 410, 300, 450, "Запустить в режиме слуйной генерации значений массива");
                    print_button_selected(364, 466, 300, 506, "Запустить в режиме считывания значений массива из файла");
	                break;
	            }
            }
            print_button(300, 522 - deductible, 300, 562 - deductible, "Выход");
            break;
        }
        case 4:
        {
            print_button(300, 130, 300, 170, "Справка");
            print_button(300, 186, 300, 226, "Задание №1 - Обработка матриц");
            print_button(300, 242, 300, 282, "Задание №2 - Решение геометрических задач");
            print_button(300, 298, 300, 338, "Задание №3 - Задачи сортировки");
            print_button_selected(300, 354, 300, 394, "Выход");
            break;
        }
    }
}

int main()
{
    setlocale(LC_ALL, "Russian");
    strcpy((char*)LfGraph.lfFaceName, "Times New Roman");
    strcpy((char*)LfMenuName.lfFaceName, "Times New Roman");
    strcpy((char*)LfMenuStrings.lfFaceName, "Times New Roman");
    hFontGraph = CreateFontIndirect(&LfGraph);
    hFontMenuName = CreateFontIndirect(&LfMenuName);
    hFontMenuStrings = CreateFontIndirect(&LfMenuStrings);
    SetTextColor(hDC, RGB(0, 0, 0));
    SetBkColor(hDC, RGB(255, 255, 255));
    GetClientRect(hWnd, &Rect);
    int main_index = 0;
    int sub_index = 0;
    int key = 0;
    do
    {
        print_menu(main_index, sub_index);
        key = _getch();
        if (key == ARROW_DOWN)
        {
            if (main_index == 4)
            {
                main_index = 0;
                continue;
            }
            else
            {
                main_index++;
                continue;
            }
        }
        if (key == ARROW_UP)
        {
            if (main_index == 0)
            {
                main_index = 4;
                continue;
            }
            else
            {
                main_index--;
                continue;
            }
        }
        if (key == ENTER || key == ARROW_RIGHT)
        {
            if (main_index != 4)
            {
                sub_index = 1;
                do
                {
                    print_menu(main_index, sub_index);
                    key = _getch();
                    if (key == ARROW_DOWN)
                    {
                        if (main_index == 0 && sub_index == 5)
                        {
                            sub_index = 1;
                            continue;
                        }
                        else if ((main_index >= 1 && main_index <= 3) && sub_index == 3)
                        {
                            sub_index = 1;
                            continue;
                        }
                        else
                        {
                            sub_index++;
                            continue;
                        }
                    }
                    if (key == ARROW_UP)
                    {
                        if (main_index == 0 && sub_index == 1)
                        {
                            sub_index = 5;
                            continue;
                        }
                        else if ((main_index >= 1 && main_index <= 3) && sub_index == 1)
                        {
                            sub_index = 3;
                            continue;
                        }
                        else
                        {
                            sub_index--;
                            continue;
                        }
                    }
                    if (key == ESC || key == ARROW_LEFT)
                    {
                        sub_index = 0;
                        continue;
                    }
                    if (key == ENTER || key == ARROW_RIGHT)
                    {
	                    if (main_index == 0)
	                    {
		                    if (sub_index == 1)
		                    {
                                system("CLS");
			                    //Справка об управлении меню
                                continue;
		                    }
                            else if(sub_index == 2)
                            {
                                system("CLS");
	                            //Справка о курсовом проекте
                                continue;
                            }
                            else if (sub_index == 3)
                            {
                                system("CLS");
                                //Справка о задании №1 - обработка матриц
                                continue;
                            }
                            else if (sub_index == 4)
                            {
                                system("CLS");
                                //Справка о задании №2 - решение геометрических задач
                                continue;
                            }
                            else if (sub_index == 5)
                            {
                                system("CLS");
                                //Справка о задании №3 - задачи сортировки
                                continue;
                            }
	                    }
                        else if(main_index == 1)
                        {
                            if (sub_index == 1)
                            {
                                matrix_processing(WITH_FILE_INPUT);
                                continue;
                            }
                            else if (sub_index == 2)
                            {
                                matrix_processing(WITH_RANDOM_GENERATION);
                                continue;
                            }
                            else if (sub_index == 3)
                            {
                                matrix_processing(WITH_KEYBOARD_INPUT);
                                continue;
                            }
                        }
                        else if (main_index == 2)
                        {
                            if (sub_index == 1)
                            {
                                solving_geometric_tasks(WITH_FILE_INPUT);
                                continue;
                            }
                            else if (sub_index == 2)
                            {
                                solving_geometric_tasks(WITH_RANDOM_GENERATION);
                                continue;
                            }
                            else if (sub_index == 3)
                            {
                                solving_geometric_tasks(WITH_KEYBOARD_INPUT);
                                continue;
                            }
                        }
                        else if (main_index == 3)
                        {
                            if (sub_index == 1)
                            {
                                sorting_tasks(WITH_FILE_INPUT);
                                continue;
                            }
                            else if (sub_index == 2)
                            {
                                sorting_tasks(WITH_RANDOM_GENERATION);
                                continue;
                            }
                            else if (sub_index == 3)
                            {
                                sorting_tasks(WITH_KEYBOARD_INPUT);
                                continue;
                            }
                        }
                    }
                } while (key != ESC && key != ARROW_LEFT);
            }
            else
            {
                break;
            }
        }
    } while (key != ESC);
    system("CLS");
    _getch();
	return 0;
}