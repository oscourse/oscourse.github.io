/**
 * The program demonstrate how to create a new child process for a specific task.
 * @author Kevin Cheng
 * @since  08/29/2017
 */

#include <sys/wait.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

int main(void) {
  pid_t child_pid;

  /* Create a child process. */
  child_pid = fork();

  /* Check if it was successful to create the child process. */ 
  if (child_pid == -1) {
    perror("fork");
    exit(EXIT_FAILURE);
  }

  /* The parent is waiting for the child to complete its task. */
  if (child_pid == 0) {
    int exec_return_value = execlp("/bin/ls", "ls", "-l", (char *) NULL);
    if (exec_return_value == -1) {
      perror("execlp");
      exit(EXIT_FAILURE);
    }
  }
  else {
    int wait_status;
    pid_t terminated_child_pid = wait(&wait_status);
    if (terminated_child_pid == -1) {
      perror("wait");
      exit(EXIT_FAILURE);
    }
    else {printf("Parent: my child %d terminates.\n", terminated_child_pid);}
    
    /* We can use the macro to examine the waiting status here. */
  }

  exit(EXIT_SUCCESS);
}
