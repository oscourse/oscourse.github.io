#include "fib.h"

int fib(int number)
{
    if (number <= 2)
        return 1;
    return fib(number-1) + fib(number-2);
}
