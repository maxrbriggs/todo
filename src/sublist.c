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
