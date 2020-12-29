/* A simple utility for editing and printing a to-do list
*  Copyright (C) 2020 Max Briggs
*
*  This program is free software: you can redistribute it and/or modify
*  it under the terms of the GNU General Public License as published by
*  the Free Software Foundation, either version 3 of the License, or
*  (at your option) any later version.
*
*  This program is distributed in the hope that it will be useful,
*  but WITHOUT ANY WARRANTY; without even the implied warranty of
*  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
*  GNU General Public License for more details.
*
*  You should have received a copy of the GNU General Public License
*  along with this program.  If not, see <https://www.gnu.org/licenses/>
*/

#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <time.h>
#include "sublist.h"
#include "todo_funcs.h"

int main(int argc, char *argv[])
{
	const int DAY_LENGTH_SECONDS = 86400;
	time_t today_t = time(NULL);
	time_t tomorrow_t = today_t + DAY_LENGTH_SECONDS;

	struct tm today_tm = *localtime(&today_t);
	struct tm tomorrow_tm = *localtime(&tomorrow_t);

	char today_iso[12];
	char tomorrow_iso[12];

	char *todo_dir_path = NULL;
	char *todo_file_path = NULL;
	FILE *todo_file = NULL;

	char *base_path = NULL;

	char *editor = NULL;

	/* create argument list for executing EDITOR on TODO_PATH */
	char * argv_list[3];

	int line_num = 0;

	if ((todo_dir_path = getenv("TODO")) == NULL) {
		fprintf(stderr, "Please define TODO environment variable for todo dir.\n");
	}

	if ((todo_file_path = getenv("TODO")) == NULL) {
		fprintf(stderr, "Please define TODO environment variable for todo file.\n");
	}

	if ((editor = getenv("EDITOR")) == NULL) {
		fprintf(stderr, "Please define EDITOR environment variable.\n");
	}

	/* Set file to append and read */
	if ((todo_file = fopen(todo_file_path, "a+")) == NULL) {
		fprintf(stderr, "Problem opening %s\n", todo_file_path);
		exit(1);
	}

	argv_list[0] = editor;
	argv_list[1] = todo_file_path;
	argv_list[2] = NULL;

	datestring(today_iso, &today_tm);
	datestring(tomorrow_iso, &tomorrow_tm);

	if (argc == 1) {
		add_date(tomorrow_iso, todo_file);
		fclose(todo_file);
		execvp(editor, argv_list);
	} else if (argc == 2 && !strcmp(argv[1], "-a")) {
		fclose(todo_file);
		execvp(editor, argv_list);
	} else if (argc == 2 && !strcmp(argv[1], "-c")) {
		line_num = find_line(today_iso, tomorrow_iso, todo_file);
		print_file(line_num, todo_file_path);
		fclose(todo_file);
	} else if (argc == 2 && !strcmp(argv[1], "-h")) {
		fclose(todo_file);
		print_help();
	} else if (argc == 3 && !strcmp(argv[1], "-s")) {
	/* non-zero length of argv[2] is implied by argv[2] existing */
		base_path = strip_filename(todo_file_path);
		strcat(base_path, argv[2]);
		if (select_subdir(base_path)) {
			strcat(base_path, "/todo.txt");
			/* open the non-default subfile */
			if ((todo_file = fopen(base_path, "a+")) == NULL) {
				fprintf(stderr, "Problem opening %s\n", base_path);
				exit(1);
			}
			add_date(tomorrow_iso, todo_file);
			fclose(todo_file);
			argv_list[1] = base_path;
			execvp(editor, argv_list);
		} else {
			fprintf(stderr, "No directory specified.\n");
		}
	} else if (argc > 2 && !strcmp(argv[1], "-a")) {
		append_text(&argv[2], argc - 2, todo_file);
		fclose(todo_file);
	} else if (argc >= 2 && (strcmp(argv[1], "-a") || strcmp(argv[1], "-c"))) {
		add_date(tomorrow_iso, todo_file);
		append_text(&argv[1], argc - 1, todo_file);
		fclose(todo_file);
	}
}
