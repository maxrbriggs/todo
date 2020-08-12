#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include "helpers.h"

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
	const char * const ARGV_LIST[] = {EDITOR, TODO_PATH, NULL};

	todo_file = fopen(TODO_PATH, "a+"); /* Set file to append and read */

	sprintf(today_iso, "%i-%02i-%02i\n", TODAY_TM.tm_year + 1900, TODAY_TM.tm_mon + 1, TODAY_TM.tm_mday);
	sprintf(tomorrow_iso, "%i-%02i-%02i\n", TOMORROW_TM.tm_year + 1900, TOMORROW_TM.tm_mon + 1, TOMORROW_TM.tm_mday);

	if (argc == 1) {
		no_args(tomorrow_iso, todo_file);

		fclose(todo_file);

		execv(EDITOR, ARGV_LIST);
	}

}
