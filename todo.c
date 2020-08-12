#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

void no_args(char *, FILE *);

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

int main(int argc, char *argv[])
{
	const int DAY_LENGTH_SECONDS = 86400;
	const time_t TODAY_T = time(NULL);
	const time_t TOMORROW_T = TODAY_T + DAY_LENGTH_SECONDS;

	const struct tm TODAY_TM = *localtime(&TODAY_T);
	const struct tm TOMORROW_TM = *localtime(&TOMORROW_T);

	char today_iso[11];
	char tomorrow_iso[11];

	const char *TODO_PATH = getenv("TODO");
	FILE *todo_file;

	const char *EDITOR = getenv("EDITOR");

	/* create argument list for executing EDITOR on TODO_PATH */
	char * const ARGV_LIST[] = {EDITOR, TODO_PATH, NULL};

	todo_file = fopen(TODO_PATH, "a+"); /* Set file to append and read */

	sprintf(today_iso, "%i-%02i-%02i\n", TODAY_TM.tm_year + 1900, TODAY_TM.tm_mon + 1, TODAY_TM.tm_mday);
	sprintf(tomorrow_iso, "%i-%02i-%02i\n", TOMORROW_TM.tm_year + 1900, TOMORROW_TM.tm_mon + 1, TOMORROW_TM.tm_mday);

	if (argc == 1) {
		no_args(tomorrow_iso, todo_file);

		printf("EDITOR: %s\nARGV_LIST[0]: %s\nARGV_LIST[1]: %s\n", EDITOR, ARGV_LIST[0], ARGV_LIST[1]);
		execv(EDITOR, ARGV_LIST);
	}
}
