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
 * Prints the statement that the child process was created.
 * If bg_flag is 0, then wait for the child process to complete and print that it exited..
*/
void parent_process_tasks(pid_t child_pid, int bg_flag) {
	printf("Child process with pid %d created\n", child_pid);
	if (bg_flag == 0) {
		waitpid(child_pid, NULL, 0);
		printf("Child process with pid %d exited\n", child_pid);
	}
	return;
}

/**
 * create - Creates a new file in the current directory with name [filename].
 * Prints an error message if the file already exists.
 */
int create(char* filename, int bg_flag) {

	pid_t pid;
	pid = fork();

	if (pid < 0)  {
		fprintf(stderr, "Fork failed\n");
		return 1;
	}
	else if (pid == 0) { //child process
		FILE *file = fopen(filename, "r"); //check if file exists
		if (file != NULL) {
			fprintf(stderr, "Error: File \"%s\" already exists\n", filename);
			exit(1);
			fclose(file);
		}
		file = fopen(filename, "w"); //Create file
		if (file == NULL) {
			fprintf(stderr, "Error creating file \"%s\"\n", filename);
			exit(1);
		}
		fclose(file);
		exit(0);
	}
	else { //parent process
		parent_process_tasks(pid, bg_flag);
	}
	return 0;
}

/**
 * update - Appends [text] to the end of file [filename], repeated [n] times.
 * Prints an error message if the file does not exist.
 */
int update(char* filename, int number, char* text, int bg_flag) {
	pid_t pid;
	pid = fork();

	if (pid < 0)  {
		fprintf(stderr, "Fork failed\n");
		return 1;
	}
	else if (pid == 0) { //child process
		FILE *file = fopen(filename, "r"); //check if file exists
		if (file == NULL) {
			fprintf(stderr, "Error: File \"%s\" does not exist\n", filename);
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
		parent_process_tasks(pid, bg_flag);
	}
	return 0;
}

/**
 * list - Displays the contents of the named file on the workstation screen.
 * Prints an error message if the file does not exist.
 */
int list(char* filename, int bg_flag) {

	pid_t pid;
	pid = fork();

	if (pid < 0)  {
		fprintf(stderr, "Fork failed\n");
		return 1;
	}
	else if (pid == 0) { //child process
		FILE *file = fopen(filename, "r"); //check if file exists
		if (file == NULL) {
			fprintf(stderr, "Error: File \"%s\" does not exist\n", filename);
			exit(1);
		}
		fclose(file);
		execl("/bin/cat", "cat", filename, NULL);
		exit(0);
	}
	else { //parent process
		parent_process_tasks(pid, bg_flag);
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
		fprintf(stderr, "Fork failed\n");
		return;
	}
	else if (pid == 0) { //child process
		execl("/bin/ls", "ls", NULL);
		exit(0);
	}
	else { //parent process
		parent_process_tasks(pid, bg_flag);
	}
	return;
}

/**
 * help - prints num_commands from command_list to the terminal, each on a newline.
*/
void help(unsigned int num_commands, const char** command_list) {
	for (unsigned int i = 0; i < num_commands; i++) {
		printf("%s\n", command_list[i]);
	}
	return;
}