/**
 * The program demonstrates a simple pthread example.
 * @author Kevin Cheng
 * @since  09/10/2017
 */

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

void *print_hello(void *arg) {
  printf("Hello, there!\n");
  pthread_exit(arg);
}

int main(void) {
  /* Create a thread, which prints a greeting message. */
  pthread_t thread_id;
  int print_hello_arg = 0;
  int ret_value = pthread_create(&thread_id,
                                 NULL,
                                 print_hello,
                                 (void *) &print_hello_arg);
  if (ret_value != 0) {
    perror("pthread_create");
    exit(EXIT_FAILURE);
  }

  /* Wait for the thread to terminate. */
  void *status;
  int join_ret_value = pthread_join(thread_id, &status);
  if (join_ret_value != 0) {
    perror("pthread_join");
    exit(EXIT_FAILURE);
  } 
  printf("Thread %lu exit status: %d.\n", thread_id, *(int*) status);
  
  exit(EXIT_SUCCESS);
}
