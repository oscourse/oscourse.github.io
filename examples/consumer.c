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
  int is_existed = access(PIPE_NAME, F_OK);
  if (is_existed < 0) {perror("access"); exit(EXIT_FAILURE);}

  /* Open a named pipe. */
  int pipe_descriptor = open(PIPE_NAME, O_RDONLY);
  if (pipe_descriptor < 0) {perror("open"); exit(EXIT_FAILURE);} 

  /* Keep sending the important message. */
  while(true) {
    char message[SIZE];
    memset(message, '\0', SIZE);
    ssize_t nbytes_read = read(pipe_descriptor, message, SIZE - 1);
    if (nbytes_read < 0) {perror("read"); exit(EXIT_FAILURE);}
    else {
      printf("%s (%ld)\n", message, nbytes_read);
      sleep(1);
    }
  }
  exit(EXIT_SUCCESS);
}
