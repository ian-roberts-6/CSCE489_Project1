/*************************************************************************************
 * shellfuncts.c - code definitions for your functions
 *
 *************************************************************************************/

#include <stdio.h>
#include "shellfuncts.h"

/*************************************************************************************
 * hello - sends hello world to the user! I'm doing proper function commenting so future
 *         coders might not find my code as painful.
 *
 *		Params:	param1 - I explain my parameters, like this is 1 for American, 2 for
 *                      Australian
 *
 *		Returns: always returns 1, no matter what. Fairly useless.
 *
 *************************************************************************************/

int hello(int param1) {
	// I'm commenting to explain that this checks param and changes the message
	if (param1 == 1)
		send_msg("Hello world!\n");
	else
		send_msg("G'day world!\n");

	// Return 1 because, why not.
	return 1;
}

/*************************************************************************************
 * hello - sends hello world to the user! I'm doing proper function commenting so future
 *         coders might not find my code as painful.
 *
 *    Params:  param2 - not a very good parameter name - something better might be
 *                      say, msgstr or sendtext
 *
 *************************************************************************************/

void send_msg(const char *param2) {
	printf("%s", param2);
}

/**
 * create - Creates a new file in the current directory with name [filename].
 * Returns 0 if successful.
 * Prints an error message and returns 1 if the file already exists.
 */
int create(char* filename) {
	return 1;
}

/**
 * update - Appends [text] to the end of file [filename], repeated [n] times.
 * Returns 0 if successful.
 * Prints an error message and returns 1 if the file does not exist.
 */
int update(char* filename, int number, char* text) {
	return 1;
}

/**
 * list - Displays the contents of the named file on the workstation screen.
 * Returns 0 if successful.
 * Prints an error message and returns 1 if the file does not exist.
 */
int list(char* filename) {
	return 1;
}

/**
 * dir - Prints a list of all files in the current directory to the screen.
 */
void dir() {

	return;
}
