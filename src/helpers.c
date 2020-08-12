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

	if (!string_found) {
		fprintf(todo_file, "%-s", tomorrow_iso);
	}
}

