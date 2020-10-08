#include <stdio.h>

typedef int ElementType;
#define NotFound (-1)

/* START: fig2_9.txt */
int BinarySearch(const ElementType A[], ElementType X, int N)
{
    int Low, Mid, High;

    Low = 0; /* 1*/
    High = N - 1;
    while (Low <= High) /* 2*/
    {

        Mid = (Low + High) / 2; /* 3*/

        if (A[Mid] < X)      /* 4*/
            Low = Mid + 1;   /* 5*/
        else if (A[Mid] > X) /* 6*/
            High = Mid - 1;  /* 7*/
        else
            return Mid; /* 8*/ /* Found */
    }
    return NotFound; /* 9*/ /* NotFound is defined as -1 */
}
/* END */

main()
{
    static int A[] = {1, 3, 5, 7, 9, 13, 15};
    const int SizeofA = sizeof(A) / sizeof(A[0]);
    int i;

    for (i = 0; i < 20; i++)
        printf("BinarySearch of %d returns %d\n",
               i, BinarySearch(A, i, SizeofA));
    return 0;
}
