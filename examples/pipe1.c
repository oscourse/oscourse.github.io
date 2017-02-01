#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <sys/types.h>
#include <unistd.h>

int main()
{
    int pfds[2];
    char buf[30];
    pid_t pid;

    /* create a pipe */
    if (pipe(pfds) == -1) {
            perror("pipe");
            exit(1);
    }

    /* fork a child */
    if ( (pid = fork()) < 0) {
	perror("fork");
	exit(1);
    }

    if ( pid == 0 ) {

        printf("Child: writing to the pipe\n");

	/* close the read end */
	close(pfds[0]);

	/* write message to parent  through the write end */
        if(write(pfds[1], "Hello", 6) <= 0) {
		perror("Child");
		exit(1);
	}

        printf("Child: exiting\n");

        exit(0);

    } else {

        printf("Parent: reading from pipe\n");

	/* close the write end */
	close(pfds[1]);

	/* read message from child through the read end */
        if( read(pfds[0], buf, 6) <= 0 ) {
		perror("Parent");
		exit(1);
	}

        printf("Parent: read \"%s\"\n", buf);

	/* wait for child to complete */
        wait(NULL);
    }
}

