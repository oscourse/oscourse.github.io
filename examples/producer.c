/**
 * This is a toy producer. For the purpose of presentation, we can remove the
 * error checking code.
 * @author Kevin Cheng
 * @since  10/09/2017
 */

#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <string.h>
#include <stdbool.h>
#include <signal.h>

#define PIPE_NAME "batman"
#define SAYING "All men have limits. They learn what they are and learn not to exceed them. I ignore mine."

/* Define the global variables. */
int pipe_descriptor = -1;

/* Define a function type: function takes an integer and return void. */
typedef void sigfunc_t(int);

/* Forward function declarations. */
sigfunc_t *install_signal_handler(int signal_number, sigfunc_t *signal_handler);
void sigint_handler(int signal);
void sigpipe_handler(int signal);

int main(void) {
  /* Install the SIGINT handler. */
  install_signal_handler(SIGINT, sigint_handler);

  /* Install the SIGPIPE handler. */
  install_signal_handler(SIGPIPE, sigpipe_handler);

  /* Create a named pipe. */
  mknod(PIPE_NAME, S_IFIFO | 0666, 0);

  /* Open a named pipe to write. */
  pipe_descriptor = open(PIPE_NAME, O_WRONLY);

  /* Keep sending the important message. */
  while(true) {
    write(pipe_descriptor, SAYING, strlen(SAYING));
  }
  exit(EXIT_SUCCESS);
}

/* Define a signal handler installer to install the handler for the given
 * signal.
 */
sigfunc_t *install_signal_handler(int signal_number,
                                  sigfunc_t *signal_handler) {
  /* Define the signal handler behavior. */
  struct sigaction action;
  action.sa_handler = signal_handler;
  sigemptyset(&(action.sa_mask));
  action.sa_flags = 0;

  /* Change the signal action based on the input signal handler. */
  struct sigaction old_action;
  int ret_value = sigaction(signal_number, &action, &old_action);
  if (ret_value < 0) {perror("sigaction"); return SIG_ERR;}

  return old_action.sa_handler;
}

/* Define the SIGINT handler. */
void sigint_handler(int signal) {
  close(pipe_descriptor);
  int is_unlinked = unlink(PIPE_NAME);
  if (is_unlinked < 0) {perror("unlink"); exit(EXIT_FAILURE);}
  else exit(EXIT_SUCCESS);
}

/* Define the SIGPIPE handler . */
void sigpipe_handler(int signal) {
  close(pipe_descriptor);
  int is_unlinked = unlink(PIPE_NAME);
  if (is_unlinked < 0) {perror("unlink"); exit(EXIT_FAILURE);}
  else exit(EXIT_SUCCESS);
}
