#include "hangman_strings.h"

/*
* Purpose:          Determine whether a char is lower-case.
*
*                   For this assignment only, YOU MAY NOT USE islower().  I
*                   want you to get experience in comparing character
*                   values.  So you will write code that checks whether c
*                   is between 'a' and 'z'.
*
* Parameter:        c   - A character.  Literally any byte value 0 to 255.
*
* Return value:     1 (true) if c is a lower-case letter (between 'a' and 'z').
*                   0 (false) otherwise.
*/
bool is_lowercase_letter(char c) {
	if (c >= 'a' && c <= 'z') 
	{
		return 1;
	}
       	return 0;
}


/*
* Purpose:          Determine whether a string contains a character.
*
*                   To determine whether the string contains the given
*                   character, you may use strlen() and a "for" loop, or
*                   you may use strchr().  Use the commands "man 3 strlen"
*                   and "man 3 strchr" to read more about these functions.
*                   Look near the end of the man page for "RETURN VALUE"
*                   for the best summary.
*
* Parameters:       string  - the string to search within
*                   ch      - the character to search for
*
* Return value:     1 if the string contains the character.
*                   0 otherwise
*/
bool string_contains_character(const char *string, char ch) {
	for (int i = 0; i < strlen(string); i++)
	{
		if (string[i] == ch)
		{
			return 1;
		}
	}
	return 0; 
}

/*
* Purpose:          Determine whether the length and contents of a secret
*                   are valid.  As described in the assignment PDF, valid
*                   secrets have a length that is no more than MAX_LENGTH
*                   (which already is defined for you in
*                   hangman_strings.h), and they must consist of only
*                   lower-case letters and the three punctuation characters
*                   '-', '\'', and ' '.
*
*                   Use strlen() to confirm that the length of the secret
*                   does not exceed MAX_LENGTH.  If it does, use printf()
*                   and MSG_LONG_SECRET_d to print an error and return
*                   false.  (Look in hangman_strings.h to see what
*                   MSG_LONG_SECRET_d represents.)
*
*                   Using a "for" loop, verify that all of the secret's
*                   characters are valid.  That is, that they are
*                   lower-case letters and the three kinds of punctuation.
*                   If any of the characters is illegal, then use printf()
*                   and MSG_INVALID_CHAR_c to print an error and return
*                   false.  (Look in hangman_strings.h to see what
*                   MSG_LONG_SECRET_d represents.)
*
*                   Hint:  You can test that a character of the string is
*                   punctuation using individual "==" comparisions, or you
*                   can use your function string_contains_character() and
*                   the string "punctuation" (which is defined for you in
*                   hangman_strings.h).
*
* Parameter:        secret  - A string that represents the secret to test.
*
* Return Value:     If the secret is valid, then return true.
*                   Otherwise return false.
*/
bool is_valid_secret(const char *secret) {
	int len = strlen(secret);
	if (len > MAX_LENGTH)
	{
		printf(MSG_LONG_SECRET_d, MAX_LENGTH);
		return false;
	}
	for (int i = 0; i < len; i++)
	{
		char ch = secret[i];
		if (!is_lowercase_letter(ch) && !string_contains_character("- '", ch)) 
		{
			printf(MSG_INVALID_CHAR_c, ch);
			return false; 
		}
	}
	return true;
}


/*
* Purpose:          Prompt for and return a character.  If the character is
*                   '\n' (end of line), then get another character.
*
* Parameter:        None.
*
* Return value:     A character.
*/
char prompt_for_and_read_character(void) {
	printf(MSG_PROMPT);
	int ch;
	while (1) {
		ch = getchar();
		if (ch == EOF)
			exit(0);
		if (ch == '\n') {
			continue;
		}
		return (char)ch;
	}
}

/*
* Purpose:
* 	 	This function runs the Hangman game using a secret phrase inputted by the user.
* 		It displays the current gallows art, the hidden phrase with underscores
*		for unguessed letters, and a list of eliminated letters in alphabetical order.
* 		The game continues until the phrase is completely guessed or the player
*  		reaches six wrong guesses.
*
* Parameters and return value:
* 	 	secret (parameter): A pointer to a null-terminated string containing the secret
* 	 	phrase to be guessed. It may include lowercase letters, spaces, hyphens, or 
* 	 	apostrophes.
* 		This function does not return anything. Instead, it prints the game's progress, 
* 		player prompts, and final win/lose messages. 
* Details:
* 		The function begins with a hidden version of the secret phrase,
 * 		replacing all lowercase letters with underscores while keeping
 * 		spaces, hyphens, and apostrophes visible. An array of 26 integers
 * 		tracks which letters have been eliminated, ensuring they are printed
 * 		alphabetically. On each iteration, the player is prompted for a guess.
 * 		If the guess appears in the phrase, the appropriate underscores are
 * 		replaced. If not, the guess is marked as eliminated and the wrong
 * 		guess counter increases. The loop ends when the phrase is fully revealed
 * 		or the player reaches six incorrect guesses. At the end, the game
 * 		prints either a win or lose message.
*/
void run_hangman(const char *secret) {
    	char phrase[MAX_LENGTH + 1];
    	int eliminated[26] = {0};
    	int n = (int)strlen(secret);
	int remaining = 0;
    	for (int i = 0; i < n; i++) {
        	char c = secret[i];
        	if (c >= 'a' && c <= 'z') {
		       	phrase[i] = '_';
		       	remaining++;
		} else
			phrase[i] = c;
    	}
	phrase[n] = '\0';
	int wrong = 0;

	// print the game display
	printf("%s\n", arts[wrong]);
        printf("    Phrase: %s\n", phrase);
        printf("Eliminated: ");
        for (int k = 0; k < 26; k++) {
        	if (eliminated[k])
                	printf("%c", 'a' + k);
                }
                printf("\n\n");

    	while (remaining > 0 && wrong < 6) {
		char input = prompt_for_and_read_character();
		int found = 0;
		for (int j = 0; j < n; j++) {
			if (input == secret[j] && phrase[j] == '_') {
				phrase[j] = input;
				remaining--;
				found = 1;
			}
		}
		if (!found) {
			if (input >= 'a' && input <= 'z') {
				int idx = input - 'a';
				if (!eliminated[idx]) {
					eliminated[idx] = 1;
					wrong++;
				}
			} else 
				wrong++;
		}
		printf("%s\n", arts[wrong]);
		printf("    Phrase: %s\n", phrase);
		printf("Eliminated: ");
		for (int k = 0; k < 26; k++) {
			if (eliminated[k])
				printf("%c", 'a' + k); 
		} printf("\n\n");
	}
	if (remaining == 0)
		printf(MSG_WIN_s, secret);
	else
		printf(MSG_LOSE_s, secret);
}

	
/*
* Purpose:          Run the hangman game.
*
*                     1. Check the value of argc to confirm that the user
*                        runs hangman with a "secret" on the command line.
*                        If the user puts the wrong number of arguments on
*                        the command line, then using printf() and
*                        MSG_WRONG_NUM_ARGS to report an error, and then
*                        "return 1".
*                     2. Call is_valid_secret().  If the function
*                        returns false, then "return 1;".
*                     3. Call run_hangman(secret).
*                     4. Return 0.
*
* Parameters:       argc    - The number of command-line arguments from main().
*                   argv    - An array of strings from main().
*
* Return value:     0 if no error.  1 otherwise.
*/
int main(int argc, char **argv) {
	if (argc != 2) 
	{
		printf(MSG_WRONG_NUM_ARGS);
		return 1;
	}
	char *secret = argv[1];
	if (!is_valid_secret(secret)) 
	{
		return 1;
	}
	run_hangman(secret);
	return 0;


	// assert(is_lowercase_letter('a'));
	// assert(!is_lowercase_letter('A'));
	// assert(!is_lowercase_letter('3'));
	// assert(string_contains_character("abc", 'a'));
	// assert(string_contains_character("abc", 'b'));
	// assert(string_contains_character("abc", 'c'));
	// assert(!string_contains_character("abc", 'd'));
	// assert(is_valid_secret("abcdefg-hijklmnop qrstuv'wxyz"));
	// assert(!is_valid_secret("A"));
	// assert(!is_valid_secret("3"));
	return 0; // Replace this line with your source code.
}
