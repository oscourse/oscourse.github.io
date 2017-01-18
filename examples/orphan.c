#include <stdio.h>
#include <sys/types.h>

int main()
{
	pid_t pid;

	if ((pid = fork()) < 0) { 
		fprintf(stderr, "fork failed\n"); 
		exit(1); 
	} 

	if (pid == 0) { 
		printf("Child pid = %d\n", getpid());
		while(1);
	} 

	printf("parent exits\n"); 
}
