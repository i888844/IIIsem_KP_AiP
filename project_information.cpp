//project_information.cpp

// This is a personal academic project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++, C#, and Java: https://pvs-studio.com

#include "common.h"
#include "project_information.h"

int project_information(int mode)
{
	FILE* file = NULL;
	switch(mode)
	{
		case (ABOUT_MENU_MANAGEMENT):
		{
			file = fopen("about_menu_management.txt", "r");
			break;
		}
		case (ABOUT_THE_COURSE_PROJECT):
		{
			file = fopen("about_the_course_project.txt", "r");
			break;
		}
		case (ABOUT_MATRIX_PROCESSING_TASKS):
		{
			file = fopen("about_matrix_processing_tasks.txt", "r");
			break;
		}

		case (ABOUT_SOLVING_GEOMETRIC_TASKS):
		{
			file = fopen("about_solving_geometric_tasks.txt", "r");
			break;
		}
		case (ABOUT_SORTING_TASKS):
		{
			file = fopen("about_sorting_tasks.txt", "r");
			break;
		}
	}
	if (file == NULL)
	{
		printf("[������]: �� ������� ������� ����.\n");
		exit(1);
	}
	int max_length = 0;
	int length = 0;
	int ch;
	while ((ch = fgetc(file)) != EOF)
	{
		if (ch != '\n')
		{
			length++;
		}
		else {
			if (length > max_length)
			{
				max_length = length;
			}
			length = 0;
		}
	}
	rewind(file);
	char* line = (char*)malloc((max_length + 1) * sizeof(char));
	while (fgets(line, max_length + 1, file))
	{
		printf("%s", line);
	}
	fclose(file);
	free(line);
	printf("\n������� ����� �������, ���� ��������� � ����...");
	_getch();
	system("CLS");
	return 0;
}