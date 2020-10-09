/**
 * 递归函数
 * 
 * @author xknower
 */
#include <stdio.h>

/* START: fig1_2.txt */
int F(int X)
{
        if (X == 0)       /* 1*/
                return 0; /* 2*/
        else
                return 2 * F(X - 1) + X * X; /* 3*/
}
/* END */

int main()
{
        printf("F(5) = %d\n", F(5));
        return 0;
}
