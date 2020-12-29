todo
====

A simple utility for managing a to-do list. The list is a simple text
file with items separated by the date.

Requirements
------------
Setting the TODO_DIR and EDITOR environment variables.

TODO_DIR
	The location of your to-do file
EDITOR
	Your prefered text editor

Usage
-----

todo [OPTION] [MESSAGE]...

With no MESSAGE, execute EDITOR on $TODO_DIR/todo.txt

Options:
	-a      Append to todo file without date
	-c      Concatenate todo file
	-h      Show this message

Examples:
	todo             Append to todo file and add date
	todo -a          Append to todo file
	todo -a example  Append "example" to todo file

Building
--------
Run 'make' to build the utility. The executable is called 'todo'.
