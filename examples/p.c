#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <sys/types.h>
#include <unistd.h>
#include <signal.h>

void pipe_handler(int arg)
{

	printf("%d got SIGPIPE\n", getpid());

}

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

    signal(SIGPIPE, pipe_handler);

    /* fork a child */
    if ( (pid = fork()) < 0) {
	perror("fork");
	exit(1);
    }

    if ( pid == 0 ) {

        printf("Child: writing to the pipe\n");
	close(pfds[0]);

        if( write(pfds[1], buf, 6) <= 0 ) {
		perror("child");
	}

        if( write(pfds[1], buf, 6) <= 0 ) {
		perror("child");
	}

        printf("Child: exiting\n");

        exit(0);

    } else {

	close( pfds[1] );

      // printf("Parent: reading from pipe\n");
//        if( read(pfds[0], buf, 6) <= 0 ) {
//		printf("Parent read error\n");
//		//exit(0);
//	}
	close(pfds[0]);

        printf("Parent: read \"%s\"\n", buf);

	/* wait for child to complete */
        //wait(NULL);

	printf("Parent Exiting\n");
    }
}

