#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>


int main()
{
	pid_t pid;
	int status;
	int ret;

	pid = fork();
 
	if (pid < 0) { 
		perror("fork failed:"); 
		exit(1); 
	} 

	if (pid == 0) { // Child executes this block
		printf("This is the child\n"); 
		exit(99); 
	} 

	if (pid > 0) { //Parent executes this block
		printf("This is parent. The child is %d\n", pid); 

		ret = waitpid(pid, &status, 0);
		if (ret < 0) {
			perror("waitpid failed:");
			exit(2); 
		}


		printf("Child exited with status %d\n", WEXITSTATUS(status));
	} 

	return 0;
}

