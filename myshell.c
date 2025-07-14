/*************************************************************************************
 * myshell - student code for Project 1 of CSCE 489 
 *
 *************************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "shellfuncts.h"
#include "helperfuncts.h"



int main(int argc, const char *argv[]) {
	(void) argv; // Make compile warnings go away - be sure to delete this line if you use the param
	(void) argc; // Make compile warnings go away - be sure to delete this line if you use the param

	int exit_sent = 0; //Flag to determine if the user sent the exit command.



	while (exit_sent == 0) {
		char user_input[100];
		fgets(user_input, sizeof(user_input), stdin);
		if (user_input[0] == '\n') {
			continue;
		}
		strip_trailing_newline(user_input);
		int num_tokens = get_num_tokens(user_input);
		char** input_tokens = parse_user_input(user_input, num_tokens);
		
		if (strcmp("exit", input_tokens[0]) == 0) {
			exit_sent = 1;
		} else {
			printf("User input has %d tokens\n", num_tokens);
			for (int i = 0; i < num_tokens; i++) {
				printf("%s\n", input_tokens[i]);
			}
		}
		
		free_string_array(input_tokens, num_tokens);
	}
	printf("Bye bye now!\n");
	return 0;
}
