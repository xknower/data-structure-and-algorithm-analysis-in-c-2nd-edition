/**
 * @author xknower
 */
#include <stdio.h>

int Sum(int N)
{
    int i, PartialSum;

    PartialSum = 0;              /* 1*/
    for (i = 0; i < N; i++)      /* 2*/
        PartialSum += i * i * i; /* 3*/

    return PartialSum; /* 4*/
}

// 时间复杂度 : O(N)
long int Factorial(int N)
{
    if (N <= 1)   /* 1*/
        return 1; /* 2*/
    else
        return N * Factorial(N - 1); /* 3*/
}

//
long int Fib(int N)
{
    if (N <= 1)   /* 1*/
        return 1; /* 2*/
    else
        return Fib(N - 1) + Fib(N - 2); /* 3*/
}

int main()
{
    printf("Sum(5) = %d\n", Sum(5));
    return 0;
}
