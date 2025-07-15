/*************************************************************************************
 * shellfuncts.c - code definitions for your functions
 *
 *************************************************************************************/

#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include "shellfuncts.h"


/**
 * create - Creates a new file in the current directory with name [filename].
 * Returns 0 if successful.
 * Prints an error message and returns 1 if the file already exists.
 */
int create(char* filename) {
	//TODO - print an error message if the file already exists. (maybe fopen with read?)
	FILE *opened_file = fopen(filename, "a");
	if (opened_file == NULL) {
		perror("Error creating file.");
		return 1;
	}
	fclose(opened_file);
	return 0;
}

/**
 * update - Appends [text] to the end of file [filename], repeated [n] times.
 * Returns 0 if successful.
 * Prints an error message and returns 1 if the file does not exist.
 */
int update(char* filename, int number, char* text) {
	//TODO - check for existence of file.
	FILE *file = fopen(filename, "a");
	int length = strlen(text);
	for (int i = 0; i < number; i++) {
		fprintf(file, "%s\n", text);
		fflush(file);
		sleep(length/5);
	}
	fclose(file);
	return 0;
}

/**
 * list - Displays the contents of the named file on the workstation screen.
 * Returns 0 if successful.
 * Prints an error message and returns 1 if the file does not exist.
 */
int list(char* filename) {
	int length = strlen(filename);
	char command[length + 5];
	FILE *file = fopen(filename, "r");
	if (file == NULL) {
		perror("File does not exist");
		return 1;
	}
	snprintf(command, length + 5, "cat %s", filename);
	execl(command, "cat", filename, NULL);
	fclose(file);
	return 0;
}

/**
 * dir - Prints a list of all files in the current directory to the screen.
 */
void dir() {
	execl("/bin/ls", "ls", NULL);
	return;
}
