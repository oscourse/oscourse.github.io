/**
 * This is a toy consumer. For the purpose of presentation, we can remove the
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

#define PIPE_NAME "batman"
#define SIZE 91

int main(void) {
  /* Check if the named pipe exists. */
  if(access(PIPE_NAME, F_OK) == -1) {perror("access"); exit(EXIT_FAILURE);}

  /* Open a named pipe to read. */
  int pipe_descriptor = open(PIPE_NAME, O_RDONLY);

  /* Keep sending the important message. */
  while(true) {
    char message[SIZE];
    memset(message, '\0', SIZE);
    read(pipe_descriptor, message, SIZE - 1);
    printf("%s\n", message);
  }
  exit(EXIT_SUCCESS);
}
