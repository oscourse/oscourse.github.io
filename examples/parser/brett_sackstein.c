//Name: Brett Sackstein
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <ctype.h>

#define MAX_LINE_LEN 10000

char line[MAX_LINE_LEN];

void tokenize (char * lineptr){
	int token_count = 0;
	char **tokens = (char**)malloc(strlen(lineptr) * sizeof(char*)); //Fixes token size constraint
	int size = strlen(lineptr);
	char* temp = (char*) malloc(size);
	while (sscanf(lineptr, "%s", temp) != EOF){
		tokens[token_count] = temp;
		printf("read token %s\n", tokens[token_count]);
		while(*lineptr == ' ' && *lineptr){ //Fixes whitespace error
			lineptr++;
		}
		lineptr += strlen(tokens[token_count]);
		token_count++;
		size = strlen(lineptr);
		temp = (char*) malloc(size);
	}
	
	printf("read %d tokens\n", token_count);
	int i;
	for( i = 0; i < token_count; i++) free(tokens[i]);
	free(temp);	
	free(tokens);

}

int main(){
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
	fclose(fp);
	return 0;
}