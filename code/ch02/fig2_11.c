/**
 * 冥运算
 * 
 * @author xknower
 */
#include <stdio.h>

#define IsEven(N) ((N) % 2 == 0)

/* START: fig2_11.txt */
long int
Pow(long int X, unsigned int N)
{
        if (N == 0)                       /* 1*/
                return 1;                 /* 2*/
        if (N == 1)                       /* 3*/
                return X;                 /* 4*/
        if (IsEven(N))                    /* 5*/
                return Pow(X * X, N / 2); /* 6*/
        else
                return Pow(X * X, N / 2) * X; /* 7*/
}
/* END */

int main()
{
        printf("2^21 = %ld\n", Pow(2, 21));
        return 0;
}
