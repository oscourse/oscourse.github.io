#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

#define MAX_TOKENS 100
#define MAX_STRING_LEN 100
#define MAX_LINE_LEN 10000

char tokens[MAX_TOKENS][MAX_STRING_LEN];
char line[MAX_LINE_LEN];

void tokenize (char * lineptr)
{
	int token_count = 0;

	while ( sscanf(lineptr, "%s", tokens[token_count]) != EOF) { // bug  here if token length is greater than 100
		printf("read token %s\n", tokens[token_count]);
		lineptr += strlen(tokens[token_count]) + 1; // bug here if there's more than two space between tokens
		token_count++;
	}

	printf("read %d tokens\n", token_count);
	
}

int main()
{
	FILE *fp;

	if ( (fp = fdopen(STDIN_FILENO, "r")) == NULL) {
		perror("error converting stdin to FILE *\n");
		exit(1);
	} 
	

	// read a line
	if ( fgets(line, MAX_LINE_LEN, fp) == NULL) {
		perror("error reading line from stdin\n");
		exit(2);
	}

	printf("read this line: %s\n", line);

	tokenize(line);
	
	return 0;
}

