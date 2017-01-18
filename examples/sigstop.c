/* This program illustrates how to use SIGCHLD to avoid zombies */

#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <sys/types.h>

/* type definition of "pointer to a function that takes integer argument and returns void */
typedef void (*sighandler_t)(int);

/* This function  installs a signal handler for 'signo' signal */
sighandler_t signal(int signo, sighandler_t handler)
{
	struct sigaction act, oact;

	act.sa_handler = handler;
	sigemptyset(&act.sa_mask);
	act.sa_flags = 0;

	if( signo == SIGALRM ) {
#ifdef SA_INTERRUPT
		act.sa_flags |= SA_INTERRUPT;  /* SunOS 4.x */
#endif
	} else {
#ifdef SA_RESTART
		act.sa_flags |= SA_RESTART;  /* SVR4, 4.4BSD */
#endif
	}

	if( sigaction(signo, &act, &oact) < 0 )
		return (SIG_ERR);

	return(oact.sa_handler);
}

pid_t pid;

/* SIGTSTP handler */
void int_handler(int sig)
{
  printf("In Parent %d: Received SIGTSTP. Stopping Child %d\n", getpid(), pid);

  kill(pid, SIGSTOP);

  printf("Parent continues...\n");
}

/* just a dummy function */
void some_processing() 
{
}

int main(int argc, char *argv[])
{

	printf("Parent %d\n", getpid());


  /* create a child */
  if ((pid = fork()) < 0)
  {
    fprintf(stderr,
	    "fork failed\n");
    exit(1);
  }

  if (pid == 0)
  {
    /* child  does nothing and completes immediately */
    printf("Child %d entering while loop\n", getpid());
    while(1);
    exit(0);
  }

  /* parent installs signal handler for SIGTSTP */
  signal(SIGTSTP, int_handler);

  /* Parent goes ahead and does some other processing */
  while(1) {
	some_processing();
  }
}
