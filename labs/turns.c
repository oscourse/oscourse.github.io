#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <assert.h>
#include <sys/types.h>
#include <sys/wait.h>

#define MAX_PROCS 1000

int mypid = 0, nextpid = 0;
int pid[MAX_PROCS+1];
int C, T;

void kickoff_handler(int signum) 
{
	static int init = 0;

	++init;

	printf("INIT %d\n", init);
	if (init >= C) {
		mypid = pid[0];
		nextpid = pid[C];
		printf("KICKOFF me %d next %d\n", mypid, nextpid);

		kill(nextpid, SIGUSR1);
	}
	
}

void turn_handler(int signum) 
{
	static int t = 0;

	t++;

	printf("MYTURN pid:%d turn:%d ", mypid, t);

	if( mypid != pid[0]) { // I am not the parent
		printf(" next:%d", nextpid);
		kill(nextpid, SIGUSR1);
	} else if (t < T) {
		printf(" next:%d", nextpid);
		kill(nextpid, SIGUSR1);
	} // else stop the cycle

	printf("\n");

	if( t >=T) {
		//printf("pid:%d exiting\n", mypid);
		exit(0);
	}
}

int main(int argc, char *argv[])
{
	int status;

	if (argc != 3) {
		printf("Usage: %s <num_children> <num_turns>\n", argv[0]);
		exit(0);
	}

	C = atoi(argv[1]);
	T = atoi(argv[2]);	

	//printf("%d %d\n", C, T);
	if (C > MAX_PROCS) {
		printf("%d is more than %d processes \n", C, MAX_PROCS);
		exit(0);
	}

	pid[0] = getpid();
	assert( signal(SIGUSR2, kickoff_handler) != SIG_ERR);
	assert( signal(SIGUSR1, turn_handler) != SIG_ERR );

	for(int c=1; c<=C; c++) {
		if ( (pid[c] = fork()) < 0) {
			printf("unable to fork child %d\n", c);
			exit(1);
		}

		if (pid[c] == 0) {
			pid[c] = getpid();
			mypid = pid[c];
			assert((c-1) >= 0);
			nextpid = pid[c-1];
			printf("me %d next %d\n", mypid, nextpid);

			assert( signal(SIGUSR1, turn_handler) != SIG_ERR );

			// tell the parent I've initialized
			sleep (1);
			printf("Tell %d\n", mypid);
			kill(pid[0], SIGUSR2);

			while(1) 
				sleep(1);
			
			assert(0);
		}
	}
	
	for(int c=1; c<=C; c++) {
		if( waitpid(pid[c], &status, 0) < 0) {
			printf("Error waiting for child %d\n", pid[c]);
		}
	}

}

