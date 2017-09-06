/**
 * The C program demonstrates how to use a function pointer.
 * @author Kevin Cheng
 * @since  09/05/2017
 */

#include <stdio.h>

/* "func" is a pointer to a function that expects an argument of integer pointer
 * and returns an integer.
 */
int (*func)(int *);

/* Mimic the pre-increment operator. What about the post increment operator? */
int pre_increment(int *x) {
  (*x) += 1;
  return *x;
}

/* Let's have some fun with the function pointer. */
int main(void) {
  func = &pre_increment; // From the C99 specification, func = pre_increment
  int x = 5;
  printf("%d\n", (*func)(&x));
  return 0;
}
