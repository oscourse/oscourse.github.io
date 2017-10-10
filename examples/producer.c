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

int main(void) {
  /* Create a named pipe. */
  mknod(PIPE_NAME, S_IFIFO | 0666, 0);

  /* Open a named pipe to write. */
  int pipe_descriptor = open(PIPE_NAME, O_WRONLY);

  /* Keep sending the important message. */
  while(true) {
    write(pipe_descriptor, SAYING, strlen(SAYING));
  }
  exit(EXIT_SUCCESS);
}
