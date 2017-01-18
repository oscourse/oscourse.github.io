#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <assert.h>
#include <ctype.h>

#define MAX_TOKENS 100
#define MAX_STRING_LEN 100
size_t MAX_LINE_LEN = 10000;

char tokens[MAX_TOKENS][MAX_STRING_LEN];
char *line;

#if 0
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
#endif

int main()
{

	FILE *fp;
	char *token, *string, *tofree;

	if ( (fp = fdopen(STDIN_FILENO, "r")) == NULL) {
		perror("error converting stdin to FILE *\n");
		exit(1);
	} 
	

	// read a line
	if ( getline(&line, &MAX_LINE_LEN, fp) == -1) {
		perror("error reading line from stdin\n");
		exit(2);
	}

#if 0
	printf("read this line: %s\n", line);

	tokenize(line);
#endif


        tofree = string = strdup(line);
        assert(string != NULL);

        while ((token = strsep(&string, " \t\n\v\f\r")) != NULL) {
		if(*token == '\0')  
			continue;
		printf("read `%s'\n", token);
	}

	free(tofree);
	
	return 0;
}

