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

/* SIGCHLD handler */
void int_handler(int sig)
{
  pid_t	pid;
  int stat;
 
  pid = wait(&stat);
  printf("In Parent: Child %d terminated\n", pid);

  printf("Parent continues...\n");
}

/* just a dummy function */
void some_processing() 
{
}

int main(int argc, char *argv[])
{
  pid_t pid;

  /* parent installs signal handler for SIGCHLD */
  signal(SIGCHLD, int_handler);

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
    printf("Child %d sleeps and then exits\n", getpid());
    sleep(2);
    exit(0);
  }

  /* Parent goes ahead and does some other processing */
  while(1) {
	some_processing();
  }
}
