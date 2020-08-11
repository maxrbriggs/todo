#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
int main(int argc, char *argv[])
{
	const int DAY_LENGTH_SECONDS = 86400;
	const time_t TODAY_T = time(NULL);
	const time_t TOMORROW_T = TODAY_T + DAY_LENGTH_SECONDS;

	const struct tm TODAY_TM = *localtime(&TODAY_T);
	const struct tm TOMORROW_TM = *localtime(&TOMORROW_T);

	const char *TODAY_ISO;
	const char *TOMORROW_ISO;

	const char *TODO_PATH = getenv("TODO");
	FILE * todo_file;

	const char *EDITOR = getenv("EDITOR");

	/* create argument list for executing EDITOR on TODO_PATH */
	char *ARGV_LIST[3];
	ARGV_LIST[0] = EDITOR;
	ARGV_LIST[1] = TODO_PATH;
	ARGV_LIST[2] = NULL;

	todo_file = fopen(TODO_PATH, "a+"); /* Set file to append and read */

	string line;

	if (argc == 1) {
		while (getline(todo_file, line)) {
			if (!strcmp(line,
		}

		fprintf(todo_file, "%i-%02i-%02i\n", TOMORROW_TM.tm_year + 1900, TOMORROW_TM.tm_mon + 1, TOMORROW_TM.tm_mday);
		execv(EDITOR, &ARGV_LIST);
	}
}
