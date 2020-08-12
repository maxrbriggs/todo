
void no_args(char *tomorrow_iso, FILE *todo_file) {
	int string_found = 0;

	char *line = NULL;
	size_t line_length = 0;

	int fprintf_return;

	while (getline(&line, &line_length, todo_file) != -1) {
		if (!strcmp(line, tomorrow_iso)) {
			printf("Tomorrow string found!\n");
			string_found = 1;
			break;
		}
	}

	if (!string_found) {
		printf("Tomorrow not found. Adding it.\n");

		fprintf_return = fprintf(todo_file, "%s\n", tomorrow_iso);

		printf("fprintf error: %i\n", fprintf_return);
	}
}

