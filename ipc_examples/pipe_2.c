/*
 Two pipes example.

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
	char * argv3[] = {"wc", 0};

	setbuf(stdout, NULL);

	int status;
	int pipefd_1[2];
	int pipefd_2[2];
	pid_t cpid1;
	pid_t cpid2;
	pid_t cpid3;

	// create a pipe
	if (pipe(pipefd_1) == -1) {
		perror("pipe");
		exit(EXIT_FAILURE);
	}
	if (pipe(pipefd_2) == -1) {
		perror("pipe");
		exit(EXIT_FAILURE);
	}

	cpid1 = fork();
	// child1 executes
	if (cpid1 == 0) {
		printf("In CHILD-1 (PID=%d): executing command %s ...\n", getpid(), argv1[0]);
		dup2(pipefd_1[1], 1);
		close(pipefd_1[0]);
		close(pipefd_1[1]);

		close(pipefd_2[0]);
		close(pipefd_2[1]);

		execvp(argv1[0], argv1);
	} 

	cpid2 = fork();
	// child2 executes
	if (cpid2 == 0) {
		printf("In CHILD-2 (PID=%d): executing command %s ...\n", getpid(), argv2[0]);
		dup2(pipefd_1[0], 0);
		close(pipefd_1[0]);
		close(pipefd_1[1]);
		
		dup2(pipefd_2[1], 1);
		close(pipefd_2[0]);
		close(pipefd_2[1]);

		execvp(argv2[0], argv2);
	} 
	
	cpid3 = fork();
	// child3 executes
	if (cpid3 == 0) {
		printf("In CHILD-3 (PID=%d): executing command %s ...\n", getpid(), argv2[0]);
		dup2(pipefd_2[0], 0);
		close(pipefd_2[0]);
		close(pipefd_2[1]);
		
		close(pipefd_1[0]);
		close(pipefd_1[1]);
		
		execvp(argv2[0], argv2);
	} 

	// parent executes
	close(pipefd_1[0]);
	close(pipefd_1[1]);
	close(pipefd_2[0]);
	close(pipefd_2[1]);

	waitpid(cpid1, &status, WUNTRACED);
	printf("In PARENT (PID=%d): successfully reaped child (PID=%d)\n", getpid(), cpid1);
	waitpid(cpid2, &status, WUNTRACED);
	printf("In PARENT (PID=%d): successfully reaped child (PID=%d)\n", getpid(), cpid2);
	waitpid(cpid3, &status, WUNTRACED);
	printf("In PARENT (PID=%d): successfully reaped child (PID=%d)\n", getpid(), cpid3);
	exit(0);

	return 0;
}
