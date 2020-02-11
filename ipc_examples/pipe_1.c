/*
 One pipe example.

 Yongheng Li
 */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/wait.h>

int main(void) {
	char * argv1[] = {"ls", "-al", "/", 0};
	char * argv2[] = {"grep", "Jun", 0};

	setbuf(stdout, NULL);

	int status;
	int pipefd[2];
	pid_t cpid1;
	pid_t cpid2;

	// create a pipe
	if (pipe(pipefd) == -1) {
		perror("pipe");
		exit(EXIT_FAILURE);
	}

	cpid1 = fork();
	// child1 executes
	if (cpid1 == 0) {
		printf("In CHILD-1 (PID=%d): executing command %s ...\n", getpid(), argv1[0]);
		dup2(pipefd[1], 1);
		close(pipefd[0]);
		close(pipefd[1]);
		execvp(argv1[0], argv1);
	} 

	cpid2 = fork();
	// child2 executes
	if (cpid2 == 0) {
		printf("In CHILD-2 (PID=%d): executing command %s ...\n", getpid(), argv2[0]);
		dup2(pipefd[0], 0);
		close(pipefd[0]);
		close(pipefd[1]);
		execvp(argv2[0], argv2);
	} 

	// parent executes
	close(pipefd[0]);
	close(pipefd[1]);
	
	waitpid(cpid1, &status, WUNTRACED);
	printf("In PARENT (PID=%d): successfully reaped child (PID=%d)\n", getpid(), cpid1);
	waitpid(cpid2, &status, WUNTRACED);
	printf("In PARENT (PID=%d): successfully reaped child (PID=%d)\n", getpid(), cpid2);
	exit(0);

	return 0;
}
