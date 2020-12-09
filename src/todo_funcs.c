#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <time.h>

/* For directory checking */
#include <dirent.h>
#include <sys/stat.h>

#include "todo_funcs.h"

/* Search todo_file for iso_date string and append it if it isn't found */
void add_date(char *iso_date, FILE *todo_file)
{
	int string_found = 0;

	char *line = NULL;
	size_t line_length = 0;

	while (getline(&line, &line_length, todo_file) != -1) {
		if (!strcmp(line, iso_date)) {
			string_found = 1;
			break;
		}
	}

	if (!string_found)
		fprintf(todo_file, "%-s", iso_date);
}

/* Find the line number location of today and tomorrow's iso date strings and
*  the length of todo_file. Return the difference between string location and
*  length of the file. Return -1 if the string location cannot be found.
*/
int find_line(char *today_iso, char *tomorrow_iso, FILE *todo_file)
{
	int today_line = 0;
	int tomorrow_line = 0;

	char *line = NULL;
	size_t line_length = 0;

	int line_num = 0;

	while (getline(&line, &line_length, todo_file) != -1) {
		++line_num;
		if (!strcmp(line, today_iso))
			today_line = line_num;
		else if (!strcmp(line, tomorrow_iso))
			tomorrow_line = line_num;
	}

	free(line);

	if (today_line > 0)
		return line_num - today_line + 1;
	else if (tomorrow_line > 0)
		return line_num - tomorrow_line + 1;
	else
		return -1;
}

/* Call tail to print the last lines of the file at path */
void print_file(int lines, char *path)
{
	char * argv_list[4];

	argv_list[0] = "tail";
	argv_list[1] = (char *) malloc(10 * sizeof(char));
	argv_list[2] = path;
	argv_list[3] = NULL;

	/* Print and quit if no today or tomorrow lines not found */
	if (lines == -1) {
		fprintf(stdout, "Nothing to do!\n");
		return;
	}

	sprintf(argv_list[1], "-n %i", lines);
	execvp("tail", argv_list);

	free(argv_list[1]);
}

/* Append text with num_words to todo_file */
void append_text(char **text, int num_words, FILE *todo_file)
{
	/* this should be long enought for anybody */
	char *todo_text = (char *)malloc(255 * sizeof(char));

	/* prime todo_text with first member */
	strcpy(todo_text, text[0]);
	for (int i = 1; i < num_words; i++) {
		strcat(todo_text, " ");
		strcat(todo_text, text[i]);
	}

	fprintf(todo_file, "\t%s\n", todo_text);

	free(todo_text);
}

/* Print help text */
void print_help()
{
	char * helpmsg = "Usage: todo [OPTION] [MESSAGE]...\nEdit or print todo file.\n\nWith no MESSAGE, execute EDITOR.\n\n  -a    Append to TODO without date\n  -c    Concatenate TODO\n  -h    Show this message\n\nExamples:\n  todo             Append to TODO and add date\n  todo -a          Append to TODO\n  todo -a example  Append \"example\" to TODO\n";

	fprintf(stdout, "%s", helpmsg);
}

/* Set iso format date string */
void datestring(char *iso_string, struct tm * date)
{
	sprintf(iso_string, "%i-%02i-%02i\n",
		date->tm_year + 1900,
		date->tm_mon + 1,
		date->tm_mday);
}

void select_subdir(char *path)
{
	DIR *test = opendir(path);
	if (test)
		/* check if directory exists */
		closedir(test);
	else if (!test)
		/* create directory if it doesn't */
		mkdir(path, 0755);
}
