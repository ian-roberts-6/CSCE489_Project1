/*************************************************************************************
 * helperfuncts.h - header file for text parsing helper functions
 *
 *************************************************************************************/

char* allocate_and_copy(char* input_string);
void free_string_array(char** string_array, int array_length);
int get_num_tokens(char* user_string);
char** parse_user_input(char* user_string, int num_tokens);
void strip_trailing_newline(char* input_string);
void strip_quotes(char* first_word, char* last_word);
