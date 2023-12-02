#include "common.h"
#include "matrix_processing.h"

double** create_matrix(int rows, int columns)
{
    double** matrix = (double**)calloc(rows, sizeof(double*));
    for (int i = 0; i < rows; i++)
    {
        matrix[i] = (double*)calloc(columns, sizeof(double));
    }
    return matrix;
}

void output_matrix(double** matrix, int columns, int rows)
{
    for (int i = 0; i < rows; i++)
    {
        for (int j = 0; j < columns; j++)
        {
            printf("%10.2lf", matrix[i][j]);
        }
        printf("\n");
    }
}

void output_matrix_to_file(double** matrix, int rows, int columns, FILE* file)
{
    for (int i = 0; i < rows; i++)
    {
        for (int j = 0; j < columns; j++)
        {
            fprintf(file, "%10.2lf ", matrix[i][j]);
        }
        fprintf(file, "\n");
    }
    fprintf(file, "\n");
}

void output_matrices_to_file(double** original_matrix, double** after_division_on_max_module, double** after_division_on_min_module, double** after_division_on_avg_main_diagonale, int rows, int columns)
{
    FILE* output_file = fopen("matrix_processing_output.txt", "w");
    if (output_file == NULL)
    {
        printf("[Ошибка]: не удалось создать файл.");
        exit(1);
    }
    fprintf(output_file, "%s", "Первоначальная матрица:\n");
    output_matrix_to_file(original_matrix, rows, columns, output_file);
    fprintf(output_file, "%s", "\nМатрица после деления на максимальный по модулю элемент:\n");
    output_matrix_to_file(after_division_on_max_module, rows, columns, output_file);
    fprintf(output_file, "%s", "\nМатрица после деления на минимальный по модулю элемент:\n");
    output_matrix_to_file(after_division_on_min_module, rows, columns, output_file);
    fprintf(output_file, "%s", "\nМатрица после деления на среднее значение главной диагонали:\n");
    output_matrix_to_file(after_division_on_avg_main_diagonale, rows, columns, output_file);
    fclose(output_file);
}

void copy_matrix(double** destination, double** source, int rows, int columns)
{
    for (int i = 0; i < rows; i++)
    {
        for (int j = 0; j < columns; j++)
        {
            destination[i][j] = source[i][j];
        }
    }
}

void free_matrix(double** matrix, int rows)
{
    for (int i = 0; i < rows; i++)
    {
        free(matrix[i]);
    }
    free(matrix);
}

void fill_matrix_rand(double** matrix, int rows, int columns)
{
    srand(time(NULL));
    for (int i = 0; i < rows; i++)
    {
        for (int j = 0; j < columns; j++)
        {
            matrix[i][j] = ((double)rand() / (double)RAND_MAX) * 200.0 - 100.0;
        }
    }
}

void fill_matrix_from_keyboard(double** matrix, int rows, int columns)
{
    printf("Введите элементы матрицы:\n");
    for (int i = 0; i < rows; i++)
    {
        for (int j = 0; j < columns; j++)
        {
            printf("Введите элемент в позиции [%f][%f]: ", i, j);
            scanf_s("%f", &matrix[i][j]);
        }
    }
}

void fill_matrix_from_file(double** matrix, int rows, int columns, const char* filename)
{
    FILE* file = fopen(filename, "r");
    if (file == NULL)
    {
        printf("[Ошибка]: Не удалось открыть файл.\n");
        exit(1);
    }
    double number = 0.0;
    srand(time(NULL));
    for (int i = 0; i < rows; i++)
    {
        for (int j = 0; j < columns; j++)
        {
            number = 0.0;
            if (fscanf(file, "%f", &number) == 1)
            {
                matrix[i][j] = number;
            }
            else
            {
                matrix[i][j] = ((double)rand() / (double)RAND_MAX) * 200.0 - 100.0;
            }
        }
    }
    fclose(file);
}

double max_module(double** matrix, int rows, int columns)
{
    double max_module_value = -999.0;
    for (int i = 0; i < rows; i++)
    {
        for (int j = 0; j < columns; j++)
        {
            if (fabs(matrix[i][j]) > max_module_value)
            {
                max_module_value = fabs(matrix[i][j]);
            }
        }
    }
    return max_module_value;
}

double min_module(double** matrix, int rows, int columns)
{
    double min_module_value = 999.0;
    for (int i = 0; i < rows; i++)
    {
        for (int j = 0; j < columns; j++)
        {
            if (fabs(matrix[i][j]) < min_module_value)
            {
                min_module_value = fabs(matrix[i][j]);
            }
        }
    }
    return min_module_value;
}

double avg_main_diagonal(double** matrix, int rows)
{
    int count_values_main_diagonale = 0;
    double avg_main_diagonale = 0.0;
    for (int i = 0; i < rows; i++)
    {
        avg_main_diagonale += matrix[i][i];
        count_values_main_diagonale++;
    }
    avg_main_diagonale /= count_values_main_diagonale;
    return avg_main_diagonale;
}

void divide_matrix(double** matrix, int rows, int columns, double divisor)
{
    for (int i = 0; i < rows; i++)
    {
        for (int j = 0; j < columns; j++)
        {
            matrix[i][j] /= divisor;
        }
    }
}

int matrix_processing(int mode)
{
    system("CLS");
    int columns = 0;
    int rows = 0;
    int cmd = 0;
    printf("Введите размер матрицы (столбцы строки): ");
    scanf_s("%i %i", &columns, &rows);
    while (columns <= 0)
    {
        printf("[Ошибка]: количество столбцов матрицы не может быть меньше или равно нулю. Введите количество столбцов матрицы: ");
        scanf_s("%i", &columns);
    }
    while (rows <= 0)
    {
        printf("[Ошибка]: количество строк матрицы не может быть меньше или равно нулю. Введите количество строк матрицы: ");
        scanf_s("%i", &rows);
    }
    double** original_matrix = create_matrix(rows, columns);
    switch (mode)
    {
        case (WITH_FILE_INPUT):
        {
            char filename[256];
            printf("Введите путь к файлу (пример: D:\\Documents\\filename.txt): ");
            scanf_s("%255s", &filename, sizeof(filename));
            fill_matrix_from_file(original_matrix, rows, columns, filename);
            break;
        }
        case (WITH_RANDOM_GENERATION):
        {
            fill_matrix_rand(original_matrix, rows, columns);
            break;
        }
        case (WITH_KEYBOARD_INPUT):
        {
            fill_matrix_from_keyboard(original_matrix, rows, columns);
            break;
        }
    }
    printf("Первоначальная матрица:\n");
    output_matrix(original_matrix, columns, rows);
    double max_module_value = max_module(original_matrix, rows, columns);
    double min_module_value = min_module(original_matrix, rows, columns);
    double avg_main_diagonale = avg_main_diagonal(original_matrix, rows);
    double** after_division_on_max_module = create_matrix(rows, columns);
    copy_matrix(after_division_on_max_module, original_matrix, rows, columns);
    divide_matrix(after_division_on_max_module, rows, columns, max_module_value);
    double** after_division_on_min_module = create_matrix(rows, columns);
    copy_matrix(after_division_on_min_module, original_matrix, rows, columns);
    divide_matrix(after_division_on_min_module, rows, columns, min_module_value);
    double** after_division_on_avg_main_diagonale = create_matrix(rows, columns);
    copy_matrix(after_division_on_avg_main_diagonale, original_matrix, rows, columns);
    divide_matrix(after_division_on_avg_main_diagonale, rows, columns, avg_main_diagonale);
    do
    {
        printf("1 - Вывести максимальный по модулю элемент и матрицу, делённую на него.\n");
        printf("2 - Вывести минимальный по модулю элемент и матрицу, делённую на него.\n");
        printf("3 - Вывести среднее арифметическое значение главной диагонали и матрицу, деленную на него.\n");
        printf("4 - Записать все матрицы в файл.\n");
        printf("0 - Вернуться в главное меню.\n");
        printf("Введите номер команды: ");
        scanf_s("%i", &cmd);
        switch (cmd)
        {
            case (0):
            {
                break;
            }
            case (1):
            {
                printf("Максимальный по модулю элемент матрицы равен: %.2f\n", max_module_value);
                output_matrix(after_division_on_max_module, rows, columns);
                break;
            }
            case (2):
            {
                printf("Минимальный по модулю элемент матрицы равен %.2f\n", min_module_value);
                output_matrix(after_division_on_min_module, rows, columns);
                break;
            }
            case (3):
            {
                printf("Среднее арефметическое значение главной диагонали матрицы равно %.2f\n", avg_main_diagonale);
                output_matrix(after_division_on_avg_main_diagonale, rows, columns);
                break;
            }
            case (4):
            {
                output_matrices_to_file(original_matrix, after_division_on_max_module, after_division_on_min_module, after_division_on_avg_main_diagonale, rows, columns);
                break;
            }
        }
    } while (cmd != 0);
    free_matrix(original_matrix, rows);
    free_matrix(after_division_on_max_module, rows);
    free_matrix(after_division_on_min_module, rows);
    free_matrix(after_division_on_avg_main_diagonale, rows);
    system("CLS");
    return 0;
}