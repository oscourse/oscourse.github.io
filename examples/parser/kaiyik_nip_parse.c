#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <ctype.h>
#define MAX_TOKENS 100
#define MAX_STRING_LEN 100

size_t MAX_LINE_LEN = 10000;

char** tokens;
char* line;


int get_token(char** lineptr, int token_count){
	int length = 0;
	
	// skip over all whitespace characters
	while(isspace(**lineptr)){
			*lineptr = *lineptr+1;
	}

	// if at end of string, no token can be read
	if(**lineptr == '\0'){
		return 0;
	}
	char* start = *lineptr;

	//read token until the next whitespace or NULL terminator
	while(!isspace(**lineptr) && **lineptr!='\0'){
		length++;
		*lineptr = *lineptr+1;
	}

	//copy this token into array of tokens
	tokens[token_count] = malloc(sizeof(char) * (length+1));
	strncpy(tokens[token_count], start, length);
	tokens[token_count][length]='\0';

	return 1;
}

void tokenize (char * lineptr)
{
	int token_count = 0;
	int size = MAX_TOKENS;
	
	// while there are more tokens to read, read.
	while (get_token(&lineptr, token_count)) {
		printf("read token '%s'\n", tokens[token_count]);		
		token_count++;
		
		if(token_count >= size){
			size*=2;

			// if there are more tokens than space ,reallocate more space
			tokens = realloc(tokens, sizeof(char*) * size);
			if(tokens == NULL){
				perror("malloc failed");
				exit(3);
			}
		}
	}

	printf("read %d tokens\n", token_count);
	
}

int main()
{
	tokens = malloc(sizeof(char*)*MAX_TOKENS);
	line = malloc(sizeof(char) * MAX_STRING_LEN);

	if(tokens == NULL || line == NULL){
		perror("malloc failed\n");
		exit(3);
	}

	FILE *fp;

	if ( (fp = fdopen(STDIN_FILENO, "r")) == NULL) {
		perror("error converting stdin to FILE *\n");
		exit(1);
	} 
	

	// get line will reallocate if input exceeds max length
	if (getline(&line, &MAX_LINE_LEN, fp) == -1) {
		perror("error reading line from stdin\n");
		exit(2);
	}	

	printf("read this line: %s\n", line);

	tokenize(line);
	
	return 0;
}
