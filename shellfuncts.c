/*************************************************************************************
 * shellfuncts.c - code definitions for your functions
 *
 *************************************************************************************/

#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include "shellfuncts.h"


/**
 * create - Creates a new file in the current directory with name [filename].
 * Returns 0 if successful.
 * Prints an error message and returns 1 if the file already exists.
 */
int create(char* filename, int bg_flag) {

	pid_t pid;
	pid = fork();

	if (pid < 0)  {
		perror("Fork failed");
		return 1;
	}
	else if (pid == 0) { //child process
		FILE *file = fopen(filename, "r"); //check if file exists
		if (file != NULL) {
			fprintf(stderr, "Error: File %s already exists", filename);
			exit(1);
		}
		fclose(file);
		file = fopen(filename, "a"); //Create file
		if (file == NULL) {
			perror("Error creating file.");
			exit(1);
		}
		fclose(file);
		exit(0);
	}
	else { //parent process
		if (bg_flag == 0) {
			wait(NULL);
		}
	}
	return 0;
}

/**
 * update - Appends [text] to the end of file [filename], repeated [n] times.
 * Returns 0 if successful.
 * Prints an error message and returns 1 if the file does not exist.
 */
int update(char* filename, int number, char* text, int bg_flag) {
	pid_t pid;
	pid = fork();

	if (pid < 0)  {
		perror("Fork failed");
		return 1;
	}
	else if (pid == 0) { //child process
		FILE *file = fopen(filename, "r"); //check if file exists
		if (file == NULL) {
			fprintf(stderr, "Error: File %s does not exist", filename);
			exit(1);
		}
		fclose(file);
		file = fopen(filename, "a");
		int length = strlen(text);
		for (int i = 0; i < number; i++) {
			fprintf(file, "%s\n", text);
			fflush(file);
			sleep(length/5);
		}
		fclose(file);
		exit(0);
	}
	else { //parent process
		if (bg_flag == 0) {
			wait(NULL);
		}
	}
	return 0;
}

/**
 * list - Displays the contents of the named file on the workstation screen.
 * Returns 0 if successful.
 * Prints an error message and returns 1 if the file does not exist.
 */
int list(char* filename, int bg_flag) {

	pid_t pid;
	pid = fork();

	if (pid < 0)  {
		perror("Fork failed");
		return 1;
	}
	else if (pid == 0) { //child process
		int length = strlen(filename);
		char command[length + 5];
		FILE *file = fopen(filename, "r"); //check if file exists
		if (file == NULL) {
			fprintf(stderr, "Error: File %s does not exist", filename);
			exit(1);
		}
		fclose(file);
		snprintf(command, length + 5, "cat %s", filename);
		execl(command, "cat", filename, NULL);
		exit(0);
	}
	else { //parent process
		if (bg_flag == 0) {
			wait(NULL);
		}
	}
	return 0;
}

/**
 * dir - Prints a list of all files in the current directory to the screen.
 */
void dir(int bg_flag) {
	pid_t pid;
	pid = fork();

	if (pid < 0)  {
		perror("Fork failed");
		return;
	}
	else if (pid == 0) { //child process
		execl("/bin/ls", "ls", NULL);
		exit(0);
	}
	else { //parent process
		if (bg_flag == 0) {
			wait(NULL);
		}
	}
	return;
}
