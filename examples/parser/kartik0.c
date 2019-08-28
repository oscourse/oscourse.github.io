#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define INPUT_BYTES 50
#define TOKEN_LENGTH 20

char *command;
char *token_list[TOKEN_LENGTH];

void parser_code(){
	char *token;
	int i = 0;
	if(fgets(command,INPUT_BYTES,stdin) != NULL){
		while((token = strsep(&command," ")) != NULL){
			token_list[i] = token;
			i++;
		}
		token_list[i] = NULL;
	}
}

int main(){
	command = malloc(INPUT_BYTES * sizeof(int));
	parser_code();
	int i=0;
	while(token_list[i] != NULL){
		printf("%s\n",token_list[i]);
		i++;
	}
}
