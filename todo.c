#include <stdio.h>
#include <stdlib.h>
int main(int argc, char *argv[])
	const char *TODO_PATH = getenv("TODO");
	FILE * todo_file;

	todo_file = fopen(TODO_PATH, "a+");

	if (argc == 1) {

	}
}
