#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <assert.h>

char *line; // original line of input
size_t max_line_len = 1000; // resizes itself

char **tokens; // list of tokens in line
int max_tokens = 100; // max allowed, can be resized
int token_count = 0; // number of tokens

// background jobs list
int *jobs;
int max_jobs = 100; // resizes itself
int job_count = 0; // Beware: Not an exact count. Includes finished jobs.

// increase tokens list to size
void add_token(char *t) 
{
	tokens[token_count] = t;
	token_count++;

	// if there are more tokens than space ,reallocate more space
	if(token_count >= max_tokens){
		max_tokens *= 2;
		assert ( tokens = realloc(tokens, sizeof(char*) * max_tokens));
	}
}

void tokenize (char * string)
{
	char *this_token;

	while ( (this_token = strsep( &string, " \t\v\f\n\r")) != NULL) {

		if (*this_token == '\0') continue; // to handle extra spaces

		add_token(this_token);
	}

	//printf("read %d tokens\n", token_count);

	//set the last token to null for later exec call; tokens_list should be long enough because we expanded the list before quitting the while loop
	tokens[token_count] = NULL;
}

void print_prompt(void) 
{
	printf("cs350sh>");
}

// read a line of input and extract tokens
void get_input(FILE * fp) 
{
	// getline will reallocate if input exceeds max length
	assert( getline(&line, &max_line_len, fp) > -1); 

	//printf("read this line: %s\n", line);

	tokenize(line);
}

int exit_command(void)
{
	return ( 
		(strcmp(tokens[0], "exit") == 0) ||
		(strcmp(tokens[0], "quit") == 0) 
	);
;
}

int background_command() 
{
	return( strcmp(tokens[token_count-1], "&") == 0 );
}

void cleanup_ampersand()
{
	assert( strcmp(tokens[token_count-1], "&") == 0 );
	tokens[token_count-1] = NULL;
	token_count--;
}

int listjobs_command(void) 
{
	return( strcmp(tokens[0], "listjobs") == 0 );
}

void add_job(int pid)
{
	int id;

	// reuse an empty id if present
	for(id=0; id< job_count; id++) 
		if( jobs[id] == -1) break;

	jobs[id]= pid;

	if( id == job_count) job_count++;

	if(job_count >= max_jobs) {
		max_jobs*=2;
		assert( jobs =realloc(jobs, max_jobs*sizeof(int))); 
	}
}

void remove_job(int id)
{
	assert(id <= job_count);
	jobs[id] = -1;
}

void list_the_background_jobs(void) 
{
	int ret, status;

	for( int i=0; i<job_count; i++) {
		if (jobs[i] == -1) continue;

		ret = waitpid(jobs[i], &status, WNOHANG);
		assert (ret != -1);

		if(ret == 0)
			printf("PID %d RUNNING\n", jobs[i]);
		else {
			assert(ret == jobs[i]);
			printf("PID %d FINISHED OR STOPPED\n", jobs[i]);
			if( status ) 
				printf("Child %d exited with status %d\n", jobs[i], WEXITSTATUS(status));
			remove_job(i);
		}
	}
}

void wait_for_child(int child_pid) 
{
	int status;

	assert(waitpid(child_pid, &status, 0) != -1);

	if( status ) 
		printf("Child %d exited with status %d\n", child_pid, WEXITSTATUS(status));
}


void run_command(void)
{
	int bg = 0;
	int ret;

	if (background_command()) {
		//printf("background command\n");
		bg = 1;
		cleanup_ampersand();
	} 

	if( listjobs_command() ) {
		list_the_background_jobs();
		return;
	}

	// fork a child
	ret = fork();
	assert(ret != -1);

	if (ret == 0) { // child
		//printf("child %d\n", getpid());

		// let it rip
		execvp(tokens[0], tokens);

		perror(tokens[0]); // bad command
		exit(1); 

	} else { // parent

		if(!bg) 
			wait_for_child(ret);
		else
			add_job(ret);
	}

}

int main()
{
	FILE *fp;

	assert( (line = malloc(sizeof(char) * max_line_len)) != NULL);
	assert( (tokens = malloc(sizeof(char*)*max_tokens)) != NULL);
	assert( (jobs = malloc(sizeof(int)*max_jobs)) != NULL);
	assert( (fp = fdopen(STDIN_FILENO, "r")) != NULL);

	while(1) {
		token_count = 0;

		print_prompt();

		get_input(fp);

		if(token_count == 0) continue; // empty command 

		if(exit_command()) break;

		run_command();
	}

	return 0;
}

