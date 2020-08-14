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

	fprintf(stderr, "today_iso: %s", today_iso);

	while (getline(&line, &line_length, todo_file) != -1) {
		looped = 1;
		++line_num;
		if (!strcmp(line, today_iso))
			today_line = line_num;
		else if (!strcmp(line, tomorrow_iso))
			tomorrow_line = line_num;
	}

	// Free if line was used
	if (looped)
		free(line);

	fprintf(stderr, "Total lines: %i\nToday line: %i\nTomorrow line: %i\n", line_num, today_line, tomorrow_line);

	if (tomorrow_line > 0)
		return (line_num - tomorrow_line);
	else if (today_line > 0)
		return (line_num - today_line);
	else
		return -1;
}

void print_file(int lines, const char *path)
{
	char * argv_list[3];

	argv_list[1] = (char *) malloc(50 * sizeof(char));

	argv_list[2] = NULL;

	if (lines <= 0) { /* if date was not found */
		argv_list[0] = "cat";
		sprintf(argv_list[1], path);
		execvp("cat", argv_list);
	} else {
		argv_list[0] = "tail";
		sprintf(argv_list[1], "-n %i %s", lines, path);
		execvp("tail", argv_list);
	}

	free(argv_list[1]);
}
