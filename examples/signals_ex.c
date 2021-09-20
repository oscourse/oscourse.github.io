#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>
#include <sys/types.h>

/* type definition of "pointer to a function that takes integer argument and returns void */
typedef void Sigfunc(int);

/* This function  installs a signal handler for 'signo' signal */
Sigfunc *install_signal_handler(int signo, Sigfunc *handler)
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

/* SIGINT handler */
void int_handler(int sig)
{
  printf("Child got SIGINT!!\n");
  exit(2);
}

int main(int argc, char *argv[])
{
  pid_t pid;

  /* create a child */
  if ((pid = fork()) < 0)
  {
    fprintf(stderr,
	    "fork failed\n");
    exit(1);
  }


  if (pid == 0)
  {
    /* child installs a signal handler */
    install_signal_handler(SIGINT, int_handler);

    /* ...and loops forever */
    while (1)
      printf("Child running amok!!!\n");
  }

  /* parent let's the child loop for some time */
  sleep(5);

  /* ... and  then interrupts it */
  printf("Parent sending SIGINT to child\n");
  kill(pid, SIGINT);
}
