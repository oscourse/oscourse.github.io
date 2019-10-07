#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <assert.h>
#include <sys/wait.h>
#include <sys/types.h>


//limits
#define MAX_TOKENS 100
#define MAX_STRING_LEN 100
#define MAX_BG_TASKS 100
size_t MAX_LINE_LEN = 10000;


// commands
#define EXIT_STR "exit"
#define EXIT_CMD 1
#define FG_STR "fg"
#define FG_CMD 2
#define LISTJOBS_STR "listjobs"
#define LISTJOBS_CMD 3

// process states
#define RUNNING 0
#define TERMINATED 1
#define STOPPED 2
static const char *status_string[] = {"RUNNING", "TERMINATED", "STOPPED"};

// misc
#define ERROR -1
#define FREE -1



FILE *fp; // file struct for stdin
char **tokens;
int token_count = 0;
char *line;

struct background_task {
	pid_t pid;
	int status;
} bgtask[MAX_BG_TASKS];
int bg_count = 0;

void initialize()
{

	// allocate space for the whole line
	assert( (line = malloc(sizeof(char) * MAX_STRING_LEN)) != NULL);

	// allocate space for individual token pointers
	assert( (tokens = malloc(sizeof(char *) * MAX_TOKENS)) != NULL);

	// open stdin as a file pointer 
	assert( (fp = fdopen(STDIN_FILENO, "r")) != NULL);

	// cleanup background task structs
	bg_count = 0;
	for(int i=0; i<MAX_BG_TASKS; i++) 
		bgtask[i].pid = FREE; 
}

void tokenize (char * string)
{
	int size = MAX_TOKENS;
	char *this_token;

	// cleanup old token pointers
	for(int i=0; i<token_count; i++) tokens[i] = NULL;

	token_count = 0;
	while ( (this_token = strsep( &string, " \t\v\f\n\r")) != NULL) {

		if (*this_token == '\0') continue;

		tokens[token_count] = this_token;

		//printf("Token %d: %s\n", token_count, tokens[token_count]);

		token_count++;

		// if there are more tokens than space ,reallocate more space
		if(token_count >= size){
			size*=2;

			assert ( (tokens = realloc(tokens, sizeof(char*) * size)) != NULL);
		}
	}
	//printf("token count = %d\n", token_count);
}

void read_command() 
{

	// getline will reallocate if input exceeds max length
	assert( getline(&line, &MAX_LINE_LEN, fp) > -1); 

	//printf("Shell read this line: %s\n", line);

	tokenize(line);
}

void handle_exit() 
{
	//printf("Exit command\n");
	
	// cleanup terminated tasks
	for(int i=0; i<MAX_BG_TASKS; i++) {
		if( bgtask[i].pid == FREE) continue;

		if (waitpid( bgtask[i].pid, NULL, WNOHANG) < 0)
			perror("error cleaning up background task:");
	}
}

void handle_listjobs() 
{
	int ret, status;

	for(int i=0; i<MAX_BG_TASKS; i++) {
		if( bgtask[i].pid == FREE) continue;

		//update status
		ret = waitpid( bgtask[i].pid, &status, WNOHANG);

		if (ret > 0) {

			if(WIFEXITED(status) || WIFSIGNALED(status)) 
				bgtask[i].status = TERMINATED;

			if(WIFSTOPPED(status)) 
				bgtask[i].status = STOPPED;
		}

		printf("PID: %d Status: %s\n", bgtask[i].pid, status_string[bgtask[i].status] );

		if(bgtask[i].status == TERMINATED) {
			bgtask[i].pid = FREE;
			bg_count--;
		}
	}
	
}

void handle_fg() 
{
	int i;
	pid_t  pid;
	int status;

	if(tokens[1] == NULL) {
		printf("Usage: fg <pid>\n");
		return;
	}

	pid = atoi(tokens[1]);

	for(i=0; i<MAX_BG_TASKS; i++) {
		if( bgtask[i].pid == pid ) break;
	}

	if(i == MAX_BG_TASKS) {
		printf("PID %d: No such background task\n", pid);
		return;
	}

	// free the entry
	bgtask[i].pid = FREE;

	//handle_listjobs();

	// block
	if( waitpid( pid, &status, 0) < 0) {
		perror("error waiting on forgrounded process:");
	}

}


int next_free_bg() 
{
	for(int i=0; i<MAX_BG_TASKS; i++) 
		if(bgtask[i].pid == FREE) return i;

	return -1;
}

int is_background() 
{
	return (strcmp(tokens[token_count-1], "&") == 0);
}

int run_command() 
{
	pid_t pid;
	int ret = 0, status;

	// handle builtin commands first

	// exit
	if (strcmp( tokens[0], EXIT_STR ) == 0) {
		handle_exit();
		return EXIT_CMD;
	}

	// fg
	if (strcmp( tokens[0], FG_STR ) == 0) {
		handle_fg();
		return FG_CMD;
	}

	// listjobs
	if (strcmp( tokens[0], LISTJOBS_STR) == 0) {
		handle_listjobs();
		return FG_CMD;
	}

	// disallow more than MAX_BG_TASKS
	if (is_background() && (bg_count == MAX_BG_TASKS) ) {
		printf("No more background tasks allowed\n");
		return ERROR;
	}

	// fork child
	pid = fork();
	if( pid < 0) {
		perror("fork failed:");
		return ERROR;
	}

	if(pid==0) {
		// exec in child
		//remove & from arguments list if background command
		if(is_background()) tokens[token_count-1] = NULL; 

		execvp(tokens[0], tokens);
		perror("exec faied:");
		exit(1);
	} else {
		if(is_background()) {
			// record bg task
			int next_free = next_free_bg();
			assert(next_free != -1); // we should have checked earlier
			bgtask[next_free].pid = pid;
			bgtask[next_free].status = RUNNING;
			bg_count++;
		} else {
			// parent waits on foreground command
			ret = waitpid(pid, &status, 0);
			if( ret < 0) {
				perror("error waiting for child:");
				return ERROR;
			}
		}
	}

	return 0;
}

int main()
{
	int ret;

	initialize();

	do {
		ret = 0;

		printf("sh550> ");

		read_command();

		if(token_count > 0) ret = run_command();

	} while( (ret != EXIT_CMD) && (ret != ERROR) );

	return 0;
}

