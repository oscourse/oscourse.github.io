#include <stdio.h>
#include "myprog.h"

void step1(void);
void step2(void);

int main()
{ 
  int i;
  step1();
  step2();
  printf("main step.\n");
  return 100;
}
