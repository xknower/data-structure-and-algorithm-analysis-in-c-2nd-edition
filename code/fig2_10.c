#include <stdio.h>

/* START: fig2_10.txt */
unsigned int
Gcd(unsigned int M, unsigned int N)
{
    unsigned int Rem;

    while (N > 0) /* 1*/
    {
        Rem = M % N; /* 2*/
        M = N;       /* 3*/
        N = Rem;     /* 4*/
    }
    return M; /* 5*/
}
/* END */

main()
{
    printf("Gcd( 45, 35 ) = %d\n", Gcd(45, 35));
    printf("Gcd( 1989, 1590 ) = %d\n", Gcd(1989, 1590));
    return 0;
}
