todo
====

A simple utility for managing a to-do list. The list is a simple text
file with items separated by the date.

Requirements
------------
Setting the TODO and EDITOR environment variables.

TODO
	The location of your to-do file
EDITOR
	Your prefered text editor

Usage
-----

todo [OPTION] [MESSAGE]...

With no MESSAGE, execute EDITOR.

Options:
	-a      Append to TODO without date
	-c      Concatenate TODO
	-h      Show this message

Examples:
	todo             Append to TODO and add date
	todo -a          Append to TODO
	todo -a example  Append "example" to TODO
