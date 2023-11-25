#include "common.h"

int* create_array(int lenght)
{
    int* array = (int*)calloc(lenght, sizeof(int));
    return array;
}

void free_array(int* array)
{
    free(array);
}

void output_array(int* array, int lenght)
{
    for (int i = 0; i < lenght; i++)
    {
        printf("%10i", array[i]);
    }
    printf("\n");
}

void output_array_with_colors(int* array, int length, int index1, int index2)
{
    for (int i = 0; i < length; i++)
    {
        if (i == index1 || i == index2)
        {
            printf(ANSI_COLOR_RED "%10i" ANSI_COLOR_RESET, array[i]);
        }
        else
        {
            printf("%10i ", array[i]);
        }
    }
    printf("\n");
}

void fill_array_rand(int* array, int lenght)
{
    srand(time(NULL));
    for (int i = 0; i < lenght; i++)
    {
        array[i] = rand() % 200 - 150;
    }
}

void fill_array_from_keyboard(int* array, int lenght)
{
    printf("������� �������� �������:\n");
    for (int i = 0; i < lenght; i++)
    {
        printf("������� ������� � ������� [%i]: ", i);
        scanf("%i", &array[i]);
        printf("\n");
    }
}

void fill_array_from_file(int* array, int lenght, const char* filename)
{
    FILE* file = fopen(filename, "r");
    if (file == NULL)
    {
        printf("[������]: �� ������� ������� ����.\n");
        exit(1);
    }
    int number = 0;
    for (int i = 0; i < lenght; i++)
    {
        number = 0;
        srand(time(NULL));
        if (fscanf(file, "%i", &number) == 1)
        {
            array[i] = number;
        }
        else
        {
            array[i] = rand() % 200 - 100;
        }
    }
    fclose(file);
}

void delete_positive_numbers(int* array, int* length)
{
    int shift = 0;
    for (int i = 0; i < *length; i++)
    {
        if (array[i] >= 0)
        {
            shift++;
        }
        else
        {
            array[i - shift] = array[i];
        }
    }
    *length -= shift;
}

void selection_sort(int* array, int length)
{
    for (int i = 0; i < length - 1; i++)
    {
        int min_index = i;
        for (int j = i + 1; j < length; j++)
        {
            if (array[j] < array[min_index])
            {
                min_index = j;
            }
        }
        if (min_index != i)
        {
            output_array_with_colors(array, length, i, min_index);
            int temp = array[i];
            array[i] = array[min_index];
            array[min_index] = temp;
            output_array_with_colors(array, length, i, min_index);
            printf("\n");
        }
    }
}

int sorting_tasks(int mode)
{
    system("CLS");
    int lenght = 0;
    int cmd = 0;
    printf("������� ����� �������: ");
    scanf_s("%i", &lenght);
    while (lenght <= 0)
    {
        printf("[������]: ����� ������� �� ����� ���� ������ ��� ����� ����. ������� ����� �������: ");
        scanf_s("%i", &lenght);
    }
    int* array = create_array(lenght);
    switch(mode)
    {
		case WITH_FILE_INPUT:
	    {
	        char filename[256];
            printf("������� ���� � ����� (������: D:\\Documents\\filename.txt): ");
	        scanf_s("%255s", &filename, sizeof(filename));
	        fill_array_from_file(array, lenght, filename);
	        break;
	    }
		case WITH_RANDOM_GENERATION:
		{
			fill_array_rand(array, lenght);
			break;
		}
		case WITH_KEYBOARD_INPUT:
		{
            fill_array_rand(array, lenght);
            break;
		}
    }
    printf("�������������� ������:\n");
    output_array(array, lenght);
    printf("\n��������� ������������� ��������:\n");
    delete_positive_numbers(array, &lenght);
    output_array(array, lenght);
    printf("\n��������� ������� ������:\n");
    selection_sort(array, lenght);
    printf("��������������� ������:\n");
    output_array(array, lenght);
    printf("\n������� ����� �������, ���� ��������� � ����...");
    _getch();
    system("CLS");
	return 0;
}