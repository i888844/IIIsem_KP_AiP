//matrix_processing.h

#pragma once
#ifndef MATRIX_PROCESSING
#define MATRIX_PROCESSING

extern double** create_matrix(int rows, int columns);
extern void output_matrix(double** matrix, int columns, int rows);
extern void copy_matrix(double** destination, double** source, int rows, int columns);
extern void free_matrix(double** matrix, int rows);
extern void fill_matrix_rand(double** matrix, int rows, int columns);
extern void fill_matrix_from_keyboard(double** matrix, int rows, int columns);
extern void fill_matrix_from_file(double** matrix, int rows, int columns, const char* filename);
extern double max_module(double** matrix, int rows, int columns);
extern double min_module(double** matrix, int rows, int columns);
extern double avg_main_diagonal(double** matrix, int rows);
extern void divide_matrix(double** matrix, int rows, int columns, double divisor);
extern int matrix_processing(int mode);

#endif