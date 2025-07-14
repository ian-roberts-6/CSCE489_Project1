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

	char user_input[] = "This is a   test   command &"; 
	int exit_sent = 0; //Flag to determine if the user sent the exit command.

	int num_tokens = get_num_tokens(user_input);
	char** input_tokens = parse_user_input(user_input, num_tokens);
	printf("User input contains %d tokens\n", num_tokens);
	for (int i = 0; i < num_tokens; i++) {
		printf("%s\n", *(input_tokens + i));
	}

	// while (!exit_sent) {
		
	// }

	free_string_array(input_tokens, num_tokens);
	return 0;
}
