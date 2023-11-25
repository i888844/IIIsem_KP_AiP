#include "common.h"

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

void fill_matrix_from_keyboard(double** matrix, int rows, int columns) {
    printf("������� �������� �������:\n");
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < columns; j++) {
            printf("������� ������� � ������� [%d][%d]: ", i, j);
            scanf_s("%lf", &matrix[i][j]);
        }
    }
}

void fill_matrix_from_file(double** matrix, int rows, int columns, const char* filename)
{
    FILE* file = fopen(filename, "r");
    if (file == NULL)
    {
        printf("[������]: �� ������� ������� ����.\n");
        exit(1);
    }
    double number = 0.0;
    srand(time(NULL));
    for (int i = 0; i < rows; i++)
    {
        for (int j = 0; j < columns; j++)
        {
            number = 0.0;
            if (fscanf(file, "%lf", &number) == 1)
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
            printf("%10.2f", matrix[i][j]);
        }
        printf("\n");
    }
}

int matrix_processing()
{
    int columns = 0;
    int rows = 0;
    int cmd = 0;
    printf("������� ������ ������� (������� ������): ");
    scanf_s("%i %i", &columns, &rows);
    while (columns <= 0)
    {
        printf("[������]: ���������� �������� ������� �� ����� ���� ������ ��� ����� ����. ������� ���������� �������� �������: ");
        scanf_s("%i", &columns);
    }
    while (rows <= 0)
    {
        printf("[������]: ���������� ����� ������� �� ����� ���� ������ ��� ����� ����. ������� ���������� ����� �������: ");
        scanf_s("%i", &rows);
    }
    double** original_matrix = create_matrix(rows, columns);
    printf("�������� ����� ���������� �������:\n");
    printf("1. ������������ ������� ��������� �������.\n");
    printf("2. ������������ ������� ������ � ����������.\n");
    printf("3. ������������ ������� ������� �� �����.\n");
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
            free_matrix(original_matrix, rows);
            return 0;
            break;
        }
        case 1:
        {
            fill_matrix_rand(original_matrix, rows, columns);
            break;
        }
        case 2:
        {
            fill_matrix_from_keyboard(original_matrix, rows, columns);
            break;
        }
        case 3:
        {
            char filename[256];
            printf("������� �������� ����� � �������� (������: filename.txt): ");
            scanf_s("%255s", &filename, sizeof(filename));
            fill_matrix_from_file(original_matrix, rows, columns, filename);
            break;
        }
    }
    output_matrix(original_matrix, columns, rows);
    double max_module_value = max_module(original_matrix, rows, columns);
    double min_module_value = min_module(original_matrix, rows, columns);
    double avg_main_diagonale = avg_main_diagonal(original_matrix, rows);
    printf("������������ �� ������ ������� ������� ����� %.2f\n", max_module_value);
    printf("����������� �� ������ ������� ������� ����� %.2f\n", min_module_value);
    printf("������� �������������� �������� ������� ��������� ������� ����� %.2f\n", avg_main_diagonale);
    printf("\n�������, ���������� ���� ������� ��������� �� ������������ �� ������ �������:\n");
    double** after_division_on_max_module = create_matrix(rows, columns);
    copy_matrix(after_division_on_max_module, original_matrix, rows, columns);
    divide_matrix(after_division_on_max_module, rows, columns, max_module_value);
    printf("\n�������, ���������� ���� ������� ��������� �� ����������� �� ������ �������:\n");
    double** after_division_on_min_module = create_matrix(rows, columns);
    copy_matrix(after_division_on_min_module, original_matrix, rows, columns);
    divide_matrix(after_division_on_min_module, rows, columns, min_module_value);
    printf("\n�������, ���������� ���� ������� ��������� �� ������� �������������� ������� ���������:\n");
    double** after_division_on_avg_main_diagonale = create_matrix(rows, columns);
    copy_matrix(after_division_on_avg_main_diagonale, original_matrix, rows, columns);
    divide_matrix(after_division_on_avg_main_diagonale, rows, columns, avg_main_diagonale);
    free_matrix(original_matrix, rows);
    free_matrix(after_division_on_max_module, rows);
    free_matrix(after_division_on_min_module, rows);
    free_matrix(after_division_on_avg_main_diagonale, rows);
    return 0;
}