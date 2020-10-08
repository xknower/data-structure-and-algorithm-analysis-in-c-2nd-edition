#include <stdio.h>

/* START: fig1_3.txt */
int Bad(unsigned int N)
{
        if (N == 0)       /* 1*/
                return 0; /* 2*/
        else
                return Bad(N / 3 + 1) + N - 1; /* 3*/
}
/* END */

main()
{
        printf("Bad is infinite recursion\n");
        return 0;
}
