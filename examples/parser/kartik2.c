#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <assert.h>

#define MAX_TOKENS 100
#define MAX_STRING_LEN 100

size_t MAX_LINE_LEN = 10000;

char **tokens;
char *line;

void tokenize (char * string)
{
	int token_count = 0;
	int size = MAX_TOKENS;
	char *this_token;

	while ( (this_token = strsep( &string, " \t\v\f\n\r")) != NULL) {

		if (*this_token == '\0') continue;

		tokens[token_count] = this_token;

		printf("read token %s\n", tokens[token_count]);

		token_count++;

		if(token_count >= size){
			size*=2;

			// if there are more tokens than space ,reallocate more space
			assert ( (tokens = realloc(tokens, sizeof(char*) * size)) != NULL);
		}
	}

	printf("read %d tokens\n", token_count);
	
}

int main()
{
	FILE *fp;

	assert( (tokens = malloc(sizeof(char*)*MAX_TOKENS)) != NULL);
	assert( (line = malloc(sizeof(char) * MAX_STRING_LEN)) != NULL);

	assert( (fp = fdopen(STDIN_FILENO, "r")) != NULL);

	// getline will reallocate if input exceeds max length
	assert( getline(&line, &MAX_LINE_LEN, fp) > -1); 

	printf("read this line: %s\n", line);

	tokenize(line);

	return 0;
}

