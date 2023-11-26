//solving_geometric_tasks.h

#pragma once
#ifndef SOLVING_GEOMETRIC_TASKS
#define SOLVING_GEOMETRIC_TASKS

typedef struct
{
    int x;
    int y;
} dot;

extern bool is_square_and_sides_not_zero(dot* square_dots);
extern bool sides_parallel_to_axes(dot* square_dots);
extern void create_dots_rand(dot* dots);
extern void create_dots_from_keyboard(dot* dots);
extern void create_dots_from_file(dot* dots, const char* filename);
extern bool in_square(dot* square_dots, dot* dot);
extern void print_line_in_axes(int x_line_start, int y_line_start, int x_line_end, int y_line_end, int number_sign_coord, int x_text, int y_text, int coord);
extern void print_axes();
extern void print_square(dot* square_dots);
extern void print_dots(dot* square_dots, dot* dots, HPEN dots_color_in_square, HPEN dots_color_out_square);
extern int solving_geometric_tasks(int mode);

#endif