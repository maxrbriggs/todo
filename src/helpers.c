#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include "helpers.h"

void no_args(char *tomorrow_iso, FILE *todo_file)
{
	int string_found = 0;

	char *line = NULL;
	size_t line_length = 0;

	while (getline(&line, &line_length, todo_file) != -1) {
		if (!strcmp(line, tomorrow_iso)) {
			string_found = 1;
			break;
		}
	}

	if (!string_found)
		fprintf(todo_file, "%-s", tomorrow_iso);
}

int find_line(char *today_iso, char *tomorrow_iso, FILE *todo_file)
{
	int looped = 0;
	int today_line = 0;
	int tomorrow_line = 0;

	char *line = NULL;
	size_t line_length = 0;

	int line_num = 0;

	while (getline(&line, &line_length, todo_file) != -1) {
		looped = 1;
		++line_num;
		if (!strcmp(line, today_iso))
			today_line = line_num;
		else if (!strcmp(line, tomorrow_iso))
			tomorrow_line = line_num;
	}

	/* Free if line was used */
	if (looped)
		free(line);

	if (today_line > 0)
		return line_num - today_line + 1;
	else
		return line_num - tomorrow_line + 1;
}

void print_file(int lines, char *path)
{
	char * argv_list[4];

	argv_list[0] = "tail";
	argv_list[1] = (char *) malloc(10 * sizeof(char));
	argv_list[2] = path;
	argv_list[3] = NULL;

	sprintf(argv_list[1], "-n %i", lines);
	execvp("tail", argv_list);

	free(argv_list[1]);
}

void append_text(char **text, int text_length, FILE *todo_file)
{
	/* this should be long enought for anybody */
	char *todo_text = (char *)malloc(255 * sizeof(char));

	/* prime todo_text with first member */
	strcpy(todo_text, text[0]);
	for (int i = 1; i < text_length; i++) {
		strcat(todo_text, " ");
		strcat(todo_text, text[i]);
	}

	fprintf(todo_file, "\t%s\n", todo_text);

	free(todo_text);
}

void print_help()
{
char * helpmsg = "Usage: todo [OPTION] [MESSAGE]...\nEdit or print todo file.\n\nWith no MESSAGE, execute EDITOR.\n\n  -a    Append to TODO without date\n  -c    Concatenate TODO\n  -h    Show this message\n\nExamples:\n  todo             Append to TODO and add date\n  todo -a          Append to TODO\n  todo -a example  Append \"example\" to TODO\n";

fprintf(stdout, "%s", helpmsg);
}
