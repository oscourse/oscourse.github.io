#include <stdio.h>
#include <sys/types.h>
#include <stdlib.h>
#include <unistd.h>

int main()
{
	pid_t pid;

	if ((pid = fork()) < 0) { 
		fprintf(stderr, "fork failed\n"); 
		exit(1); 
	} 

	if (pid == 0) { 
		if( execlp("echo", 
			"echo", 
			"Hello from the child", 
			(char *) NULL) == -1) 
		fprintf(stderr, "execl failed\n"); 

		exit(2); 
	} 

	//printf("parent sleeps for 5 seconds\n"); 
	//sleep(5);
	printf("parent(%d) carries on\n", getpid()); 
}
