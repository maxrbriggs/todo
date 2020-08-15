#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <time.h>
#include "helpers.h"

int main(int argc, char *argv[])
{
	const int DAY_LENGTH_SECONDS = 86400;
	time_t today_t = time(NULL);
	time_t tomorrow_t = today_t + DAY_LENGTH_SECONDS;

	struct tm today_tm = *localtime(&today_t);
	struct tm tomorrow_tm = *localtime(&tomorrow_t);

	char today_iso[12];
	char tomorrow_iso[12];

	char *todo_path;
	FILE *todo_file;

	char *editor;

	/* create argument list for executing EDITOR on TODO_PATH */
	char * argv_list[3];

	int line_num = 0;

	if ((todo_path = getenv("TODO")) == NULL) {
		fprintf(stderr, "Please define TODO environment variable for todo file.\n");
	}

	if ((editor = getenv("EDITOR")) == NULL) {
		fprintf(stderr, "Please define EDITOR environment variable.\n");
	}

	/* Set file to append and read */
	if ((todo_file = fopen(todo_path, "a+")) == NULL) {
		fprintf(stderr, "Problem opening %s\n", todo_path);
		exit(1);
	}

	argv_list[0] = editor;
	argv_list[1] = todo_path;
	argv_list[2] = NULL;

	/* Set iso date strings for today and tomorrow */
	sprintf(today_iso, "%i-%02i-%02i\n",
		today_tm.tm_year + 1900,
		today_tm.tm_mon + 1,
		today_tm.tm_mday);
	sprintf(tomorrow_iso, "%i-%02i-%02i\n",
		tomorrow_tm.tm_year + 1900,
		tomorrow_tm.tm_mon + 1,
		tomorrow_tm.tm_mday);

	if (argc == 1) {
		no_args(tomorrow_iso, todo_file);
		fclose(todo_file);
		execvp(editor, argv_list);
	} else if (argc == 2 && !strcmp(argv[1], "-a")) {
		fclose(todo_file);
		execvp(editor, argv_list);
	} else if (argc == 2 && !strcmp(argv[1], "-c")) {
		line_num = find_line(today_iso, tomorrow_iso, todo_file);
		print_file(line_num, todo_path);
		fclose(todo_file);
	} else if (argc == 2 && !strcmp(argv[1], "-h")) {
		fclose(todo_file);
		print_help();
	} else if (argc > 2 && !strcmp(argv[1], "-a")) {
		append_text(&argv[2], argc - 2, todo_file);
		fclose(todo_file);
	} else if (argc >= 2 && (strcmp(argv[1], "-a") || strcmp(argv[1], "-c"))) {
		no_args(tomorrow_iso, todo_file);
		append_text(&argv[1], argc - 1, todo_file);
		fclose(todo_file);
	}
}
