/*************************************************************************************
 * myshell - student code for Project 1 of CSCE 489 
 *
 *************************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "shellfuncts.h"
#include "helperfuncts.h"

//The index of the string in this array is used to determine which string to execute.
const char* COMMAND_STRINGS[] = { 
	"create",
	"update",
	"list",
	"dir",
	"help",
	"halt"
};
//Need to maintain the length of this array separately due to scoping issues.
const int NUM_VALID_COMMANDS = 6; 
unsigned int INPUT_BUFFER_SIZE = 200;

/** 
 * find_command_index - compares user input with the list of command strings to determine which one to execute.
 * Returns -1 if the string is not found in the COMMAND_STRINGS array. 
*/
unsigned int find_command_index(char* user_command) {
	for (int i = 0; i < NUM_VALID_COMMANDS; i++) {
		if (strcmp(COMMAND_STRINGS[i], user_command) == 0) {
			return i;
		}
	}
	return -1;
}

/**
 * Main shell method, implements REPL with instructor-specified commands.
*/
int main(int argc, const char *argv[]) {
	(void) argv; // Make compile warnings go away - be sure to delete this line if you use the param
	(void) argc; // Make compile warnings go away - be sure to delete this line if you use the param

	int exit_sent = 0; //Flag to determine if the user sent the exit command.

	while (exit_sent == 0) {
		pid_t pid = getpid();
		char user_input[INPUT_BUFFER_SIZE];
		printf("[%d] SHELL>", pid);
		fgets(user_input, sizeof(user_input), stdin);	//Read user input
		if (user_input[0] == '\n') {					//Check for empty input
			continue;
		}
		strip_trailing_newline(user_input);
		int num_tokens = get_num_tokens(user_input);	//Tokenize input
		char** input_tokens = parse_user_input(user_input, num_tokens);
		int bg_flag = 0;
		if (strcmp(input_tokens[num_tokens - 1], "&") == 0) { //Determine if the user wants the task in the background.
			bg_flag = 1;
		}
		switch (find_command_index(input_tokens[0])) {	//Find command
			case 0: //create
				if (num_tokens < 2+bg_flag) {
					printf("Correct usage: create <filename>\n");
				} else {
					create(input_tokens[1], bg_flag);
				}
				break;

			case 1: //update
				if (num_tokens < 4+bg_flag) {
					printf("Correct usage: update <filename> <number of lines> <text>\n");
				} else {
					char text[INPUT_BUFFER_SIZE];
					strcpy(text, input_tokens[3]);
					for (int i = 4; i < (num_tokens - bg_flag); i++) {
						strcat(text, " ");
						strcat(text, input_tokens[i]);
					}
					update(input_tokens[1], atoi(input_tokens[2]), text, bg_flag);
				}
				break;

			case 2: //list
				if (num_tokens < 2+bg_flag) {
					printf("Correct usage: list <filename>\n");
				} else {
					list(input_tokens[1], bg_flag);
				}
				break;
			case 3: //dir
				dir(bg_flag);
				break;

			case 4: //help
				help(NUM_VALID_COMMANDS, COMMAND_STRINGS);
				break;

			case 5: //halt
				exit_sent = 1;
				break;
			default:
				printf("Command \"%s\" not recognized. Type \"help\" for a list of commands.\n", input_tokens[0]);
		}
		
		free_string_array(input_tokens, num_tokens);	//Clear string array between uses.
	}
	printf("Bye bye now!\n");
	return 0;
}
