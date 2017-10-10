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
  sigfunc_t *return_handler = install_signal_handler(SIGINT, sigint_handler);
  if (return_handler == SIG_ERR) {perror("sigint"); exit(EXIT_FAILURE);}

  /* Install the SIGPIPE handler. */
  return_handler = install_signal_handler(SIGPIPE, sigpipe_handler);
  if (return_handler == SIG_ERR) {perror("sigpipe"); exit(EXIT_FAILURE);}

  /* Create a named pipe. */
  int is_named_pipe = mknod(PIPE_NAME, S_IFIFO | 0666, 0);
  if (is_named_pipe < 0) {perror("mknod"); exit(EXIT_FAILURE);} 

  /* Open a named pipe. */
  pipe_descriptor = open(PIPE_NAME, O_WRONLY);
  if (pipe_descriptor < 0) {perror("open"); exit(EXIT_FAILURE);} 

  /* Keep sending the important message. */
  while(true) {
    ssize_t nbytes_written = write(pipe_descriptor, SAYING, strlen(SAYING));
    if (nbytes_written < 0) {perror("write"); exit(EXIT_FAILURE);}
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
  if (ret_value < 0) {
    perror("sigaction");
    return SIG_ERR;
  }

  return old_action.sa_handler;
}

/* Define the interrupt signal. */
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
