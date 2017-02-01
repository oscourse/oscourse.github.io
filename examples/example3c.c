#include <stdio.h>

#define sum(a, b) ((a)+(b))
#define product(a, b) ((a)*(b))

int main() 
{
  int i;
  printf("sum(5, 10) = %d\n", sum(5, 10));
  printf("product(5, 10) = %d\n", product(5, 10));
  
  printf("10* sum(2, 3) = %d\n", 10 * sum(2, 3));
  printf("product(2+3, 5+5) = %d\n", product(2+3, 5+5));  
  return 0;
}
