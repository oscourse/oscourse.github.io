#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>


int main()
{
	pid_t pid;

	pid = fork();
 
	if (pid == -1) { 
		fprintf(stderr, "fork failed\n"); 
		exit(1); 
	} 

	if (pid == 0) { 
		printf("This is the child\n"); 
		exit(0); 
	} 

	if (pid > 0) { 
		printf("This is parent. The child is %d\n", pid); 
		exit(0); 
	} 

	return 0;
}

