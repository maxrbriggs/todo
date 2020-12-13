#include <stdlib.h>
#include <dirent.h>
#include <string.h>

#include "sublist.h"

/* Selects a sublist directory. Returns 1 if  directory exists, 0 if not */
int select_subdir(char *path)
{
	DIR *test = opendir(path);
	if (test) {
		closedir(test);
		return 1;
	} else {
		return 0;
	}
}

/* Strip the filename from a file path. Returns directory path of
*  passed filename
*/
char * strip_filename(char * file_path) {
	int path_length = 0;
	/* this is not freed! need to call free on returned pointer to
	*  not leak memory!
	*/
	char * new_path = (char *) malloc(256 * sizeof(char));
	char * path_end = strrchr(file_path, '/');

	/* loop through string, copying chars to new string */
	while (&file_path[path_length] != path_end) {
		new_path[path_length] = file_path[path_length];
		path_length++;
	}

	new_path[path_length] = '/';
	path_length++;
	new_path[path_length] = '\0';

	return new_path;
}
