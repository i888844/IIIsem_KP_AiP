//sorting_tasks.h
#pragma once
#ifndef SORTING_TASKS
#define SORTING_TASKS

extern int* create_array(int lenght);
extern void free_array(int* array);
extern void output_array_with_colors(int* array, int length, int index1, int index2);
extern void fill_array_rand(int* array, int lenght);
extern void fill_array_from_keyboard(int* array, int lenght);
extern void fill_array_from_file(int* array, int lenght, const char* filename);
extern void delete_positive_numbers(int* array, int* length);
extern void selection_sort(int* array, int length);
extern int sorting_tasks(int mode);

#endif