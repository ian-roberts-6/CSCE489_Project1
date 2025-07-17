#include <stdlib.h>
#include <string.h>


/**
 * allocate_and_copy - allocates heap memory and copies input_string into it, returns a pointer to allocated memory.
 * NOTE: this function allocates memory that must be freed.
*/
char* allocate_and_copy(char* input_string) {
	int string_length = strlen(input_string);
	char* string_copy = calloc(string_length + 1, sizeof(char));
	strncpy(string_copy, input_string, string_length);
	return string_copy;
}

/**
 * free_string_array - frees all heap memory from string_array, including the array itself. 
*/
void free_string_array(char** string_array, int array_length) {
	if (string_array == NULL) {
		return;
	}
	for (int i = 0; i < array_length; i++) {
		free(string_array[i]);
	}
	free(string_array);
	return;
}


/**
 * get_num_tokens - returns the number of tokens in user_string that the strtok function finds. 
 * 
*/
int get_num_tokens(char* user_string) {
	char* user_string_copy = allocate_and_copy(user_string);
	int num_tokens = 0;
	if (strtok(user_string_copy, " ") != NULL) {
		num_tokens = 1;
		while (strtok(NULL, " ") != NULL) {
			num_tokens++;
		}
	}
	free(user_string_copy);
	return num_tokens;
}

/**
 * parse_user_input - parses a user-provided null-terminated string into an array of tokens separated by spaces.
 * Writes the array of strings to (parsed_string)
 * NOTE: allocates memory to return pointer that must be freed. 
 * 
*/
char** parse_user_input(char* user_string, int num_tokens) {
	int i = 0;
	int string_length = strlen(user_string);
	char* current_token;
	char* user_string_copy = calloc(string_length + 1, sizeof(char));
	strncpy(user_string_copy, user_string, string_length);
	char** parsed_string = calloc(num_tokens, sizeof(char*));
	current_token = strtok(user_string_copy, " ");
	while (current_token != NULL) {
		*(parsed_string + i) = allocate_and_copy(current_token);
		current_token = strtok(NULL, " ");
		i++;
	}
	free(user_string_copy);
	return parsed_string;
}

/**
 * strip_trailing_newline - strip a trailing newline off of a string. 
 * 
*/
void strip_trailing_newline(char* input_string) {
	int string_length = strlen(input_string);
	if (input_string[string_length - 1] == '\n') {
		input_string[string_length - 1] = '\0';
	}
	return;

}

/**
 * strip_quotes - removes leading quote from first_word and trailing quote from last_word.
 * 
*/
void strip_quotes(char* first_word, char* last_word) {
	int first_word_length = strlen(first_word);
	if (first_word[0] == '"') {
		for (int i = 0; i < first_word_length - 1; i++) {
			first_word[i] = first_word[i + 1];
		}
		first_word[first_word_length - 1] = '\0';
	}
	int last_word_length = strlen(last_word);
	if (last_word[last_word_length - 1] == '"') {
		last_word[last_word_length - 1] = '\0';
	}
	return;
}