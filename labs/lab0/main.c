#include <stdio.h>
#include <stdlib.h>
#include "fib.h"

int main(int argc, char* argv[])
{
    if (argc == 1)
    {
        printf("Usage: %s number\n", argv[0]);
        return 1;
    }
    int number = atoi(argv[1]);

    if (number <= 0)
    {
        printf("Argument must be a positive integer\n");
        return 1;
    }

    int result = fib(number);
    printf("%d\n", result);

    return 0;
}
