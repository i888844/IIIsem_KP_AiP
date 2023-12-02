#pragma once
#ifndef CONTROL_MENU
#define CONTROL_MENU

extern void print_button(int left, int top, int right, int bottom, const char* string);
extern void print_button_selected(int left, int top, int right, int bottom, const char* string);
extern void print_menu(int main_index, int sub_index);
extern int control_menu();

#endif