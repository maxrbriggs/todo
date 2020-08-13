#include <stdio.h>
#include "helpers.h"

void no_args(char *tomorrow_iso, FILE *todo_file) {
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

void find_line(char *today_iso, char *tomorrow_iso, FILE *todo_file) {
	int today_line = 0;
	int tomorrow_line = 0;

	char *line = NULL;
	size_t line_length = 0;

	int line = 0;

	while (getline(&line, &line_length, todo_file) != -1) {
		++line;

		if (!strcmp(line, today_iso))
			today_line = line;
		else if (!strcmp(line, tomorrow_iso))
			tomorrow_line = line;
	}
}
