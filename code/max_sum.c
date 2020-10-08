#include <stdio.h>

/* Define one of CubicAlgorithm, QuadraticAlgorithm, NlogNAlgorithm,
 * or LinearAlgorithm to get one algorithm compiled */

#define NlogNAlgorithm

#ifdef CubicAlgorithm

/* START: fig2_5.txt */
int MaxSubsequenceSum(const int A[], int N)
{
        int ThisSum, MaxSum, i, j, k;

        MaxSum = 0;                     /* 1*/
        for (i = 0; i < N; i++)         /* 2*/
                for (j = i; j < N; j++) /* 3*/
                {
                        ThisSum = 0;             /* 4*/
                        for (k = i; k <= j; k++) /* 5*/
                                ThisSum += A[k]; /* 6*/

                        if (ThisSum > MaxSum)     /* 7*/
                                MaxSum = ThisSum; /* 8*/
                }
        return MaxSum; /* 9*/
}
/* END */

#endif

#ifdef QuadraticAlgorithm

/* START: fig2_6.txt */
int MaxSubsequenceSum(const int A[], int N)
{
        int ThisSum, MaxSum, i, j;

        MaxSum = 0;             /* 1*/
        for (i = 0; i < N; i++) /* 2*/
        {
                ThisSum = 0;            /* 3*/
                for (j = i; j < N; j++) /* 4*/
                {
                        ThisSum += A[j]; /* 5*/

                        if (ThisSum > MaxSum)     /* 6*/
                                MaxSum = ThisSum; /* 7*/
                }
        }
        return MaxSum; /* 8*/
}
/* END */

#endif

#ifdef NlogNAlgorithm

static int
Max3(int A, int B, int C)
{
        return A > B ? A > C ? A : C : B > C ? B : C;
}

/* START: fig2_7.txt */
static int
MaxSubSum(const int A[], int Left, int Right)
{
        int MaxLeftSum, MaxRightSum;
        int MaxLeftBorderSum, MaxRightBorderSum;
        int LeftBorderSum, RightBorderSum;
        int Center, i;

        if (Left == Right) /* 1*/       /* Base case */
                if (A[Left] > 0)        /* 2*/
                        return A[Left]; /* 3*/
                else
                        return 0; /* 4*/

        Center = (Left + Right) / 2;                   /* 5*/
        MaxLeftSum = MaxSubSum(A, Left, Center);       /* 6*/
        MaxRightSum = MaxSubSum(A, Center + 1, Right); /* 7*/

        MaxLeftBorderSum = 0;
        LeftBorderSum = 0;               /* 8*/
        for (i = Center; i >= Left; i--) /* 9*/
        {
                LeftBorderSum += A[i];                    /*10*/
                if (LeftBorderSum > MaxLeftBorderSum)     /*11*/
                        MaxLeftBorderSum = LeftBorderSum; /*12*/
        }

        MaxRightBorderSum = 0;
        RightBorderSum = 0;                   /*13*/
        for (i = Center + 1; i <= Right; i++) /*14*/
        {
                RightBorderSum += A[i];                     /*15*/
                if (RightBorderSum > MaxRightBorderSum)     /*16*/
                        MaxRightBorderSum = RightBorderSum; /*17*/
        }

        return Max3(MaxLeftSum, MaxRightSum,               /*18*/
                    MaxLeftBorderSum + MaxRightBorderSum); /*19*/
}

int MaxSubsequenceSum(const int A[], int N)
{
        return MaxSubSum(A, 0, N - 1);
}
/* END */

#endif

#ifdef LinearAlgorithm
/* START: fig2_8.txt */
int MaxSubsequenceSum(const int A[], int N)
{
        int ThisSum, MaxSum, j;

        ThisSum = MaxSum = 0;   /* 1*/
        for (j = 0; j < N; j++) /* 2*/
        {
                ThisSum += A[j]; /* 3*/

                if (ThisSum > MaxSum)     /* 4*/
                        MaxSum = ThisSum; /* 5*/
                else if (ThisSum < 0)     /* 6*/
                        ThisSum = 0;      /* 7*/
        }
        return MaxSum; /* 8*/
}
/* END */

#endif

main()
{
        static int A[] = {4, -3, 5, -2, -1, 2, 6, -2};

        printf("Maxsum = %d\n",
               MaxSubsequenceSum(A, sizeof(A) / sizeof(A[0])));
        return 0;
}
