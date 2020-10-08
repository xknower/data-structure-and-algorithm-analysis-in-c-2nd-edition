/* This file contains a collection of sorting routines */

#include <stdlib.h>
#include "fatal.h"

typedef int ElementType;

void Swap(ElementType *Lhs, ElementType *Rhs)
{
    ElementType Tmp = *Lhs;
    *Lhs = *Rhs;
    *Rhs = Tmp;
}

/* START: fig7_2.txt */
void InsertionSort(ElementType A[], int N)
{
    int j, P;
    ElementType Tmp;

    for (P = 1; P < N; P++) /* 1*/
    {
        Tmp = A[P];                               /* 2*/
        for (j = P; j > 0 && A[j - 1] > Tmp; j--) /* 3*/
            A[j] = A[j - 1];                      /* 4*/
        A[j] = Tmp;                               /* 5*/
    }
}
/* END */

/* START: fig7_4.txt */
void Shellsort(ElementType A[], int N)
{
    int i, j, Increment;
    ElementType Tmp;

    for (Increment = N / 2; Increment > 0; Increment /= 2) /* 1*/
        for (i = Increment; i < N; i++)                    /* 2*/
        {
            Tmp = A[i];                                 /* 3*/
            for (j = i; j >= Increment; j -= Increment) /* 4*/
                if (Tmp < A[j - Increment])             /* 5*/
                    A[j] = A[j - Increment];            /* 6*/
                else
                    break; /* 7*/
            A[j] = Tmp;    /* 8*/
        }
}
/* END */

/* START: fig7_8.txt */

#define LeftChild(i) (2 * (i) + 1)

void PercDown(ElementType A[], int i, int N)
{
    int Child;
    ElementType Tmp;

    for (Tmp = A[i]; LeftChild(i) < N; i = Child) /* 1*/
    {
        Child = LeftChild(i);                          /* 2*/
        if (Child != N - 1 && A[Child + 1] > A[Child]) /* 3*/
            Child++;                                   /* 4*/
        if (Tmp < A[Child])                            /* 5*/
            A[i] = A[Child];                           /* 6*/
        else
            break; /* 7*/
    }
    A[i] = Tmp; /* 8*/
}

void Heapsort(ElementType A[], int N)
{
    int i;

    for (i = N / 2; i >= 0; i--) /* 1*/ /* BuildHeap */
        PercDown(A, i, N);              /* 2*/
    for (i = N - 1; i > 0; i--)         /* 3*/
    {
        Swap(&A[0], &A[i]); /* 4*/ /* DeleteMax */
        PercDown(A, 0, i);         /* 5*/
    }
}
/* END */

/* START: fig7_10.txt */
/* Lpos = start of left half, Rpos = start of right half */

void Merge(ElementType A[], ElementType TmpArray[],
           int Lpos, int Rpos, int RightEnd)
{
    int i, LeftEnd, NumElements, TmpPos;

    LeftEnd = Rpos - 1;
    TmpPos = Lpos;
    NumElements = RightEnd - Lpos + 1;

    /* main loop */
    while (Lpos <= LeftEnd && Rpos <= RightEnd)
        if (A[Lpos] <= A[Rpos])
            TmpArray[TmpPos++] = A[Lpos++];
        else
            TmpArray[TmpPos++] = A[Rpos++];

    while (Lpos <= LeftEnd) /* Copy rest of first half */
        TmpArray[TmpPos++] = A[Lpos++];
    while (Rpos <= RightEnd) /* Copy rest of second half */
        TmpArray[TmpPos++] = A[Rpos++];

    /* Copy TmpArray back */
    for (i = 0; i < NumElements; i++, RightEnd--)
        A[RightEnd] = TmpArray[RightEnd];
}
/* END */

/* START: fig7_9.txt */
void MSort(ElementType A[], ElementType TmpArray[],
           int Left, int Right)
{
    int Center;

    if (Left < Right)
    {
        Center = (Left + Right) / 2;
        MSort(A, TmpArray, Left, Center);
        MSort(A, TmpArray, Center + 1, Right);
        Merge(A, TmpArray, Left, Center + 1, Right);
    }
}

void Mergesort(ElementType A[], int N)
{
    ElementType *TmpArray;

    TmpArray = malloc(N * sizeof(ElementType));
    if (TmpArray != NULL)
    {
        MSort(A, TmpArray, 0, N - 1);
        free(TmpArray);
    }
    else
        FatalError("No space for tmp array!!!");
}
/* END */

/* START: fig7_13.txt */
/* Return median of Left, Center, and Right */
/* Order these and hide the pivot */

ElementType
Median3(ElementType A[], int Left, int Right)
{
    int Center = (Left + Right) / 2;

    if (A[Left] > A[Center])
        Swap(&A[Left], &A[Center]);
    if (A[Left] > A[Right])
        Swap(&A[Left], &A[Right]);
    if (A[Center] > A[Right])
        Swap(&A[Center], &A[Right]);

    /* Invariant: A[ Left ] <= A[ Center ] <= A[ Right ] */

    Swap(&A[Center], &A[Right - 1]); /* Hide pivot */
    return A[Right - 1];             /* Return pivot */
}
/* END */

/* START: fig7_14.txt */
#define Cutoff (3)

void Qsort(ElementType A[], int Left, int Right)
{
    int i, j;
    ElementType Pivot;

    if (Left + Cutoff <= Right) /* 1*/
    {
        Pivot = Median3(A, Left, Right); /* 2*/
        i = Left;
        j = Right - 1; /* 3*/
        for (;;)       /* 4*/
        {
            while (A[++i] < Pivot)
            {
            } /* 5*/
            while (A[--j] > Pivot)
            {
            }                       /* 6*/
            if (i < j)              /* 7*/
                Swap(&A[i], &A[j]); /* 8*/
            else
                break; /* 9*/
        }
        Swap(&A[i], &A[Right - 1]); /*10*/ /* Restore pivot */

        Qsort(A, Left, i - 1);  /*11*/
        Qsort(A, i + 1, Right); /*12*/
    }
    else                                           /* Do an insertion sort on the subarray */
        InsertionSort(A + Left, Right - Left + 1); /*13*/
}
/* END */

/* This code doesn't work; it's Figure 7.15. */
#if 0
/* START: fig7_15.txt */
         i = Left + 1; j = Right - 2; /* 3*/ 
          for( ; ; ) /* 4*/
                {
              while( A[ i ] < Pivot ) i++; /* 5*/
              while( A[ j ] > Pivot ) j--; /* 6*/
             if( i < j ) /* 7*/ 
                  Swap( &A[ i ], &A[ j ] ); /* 8*/
                    else
                  break; /* 9*/
                }
/* END */
#endif

/* START: fig7_12.txt */
void Quicksort(ElementType A[], int N)
{
    Qsort(A, 0, N - 1);
}
/* END */

/* START: fig7_16.txt */
/* Places the kth smallest element in the kth position */
/* Because arrays start at 0, this will be index k-1 */
void Qselect(ElementType A[], int k, int Left, int Right)
{
    int i, j;
    ElementType Pivot;

    if (Left + Cutoff <= Right) /* 1*/
    {
        Pivot = Median3(A, Left, Right); /* 2*/
        i = Left;
        j = Right - 1; /* 3*/
        for (;;)       /* 4*/
        {
            while (A[++i] < Pivot)
            {
            } /* 5*/
            while (A[--j] > Pivot)
            {
            }                       /* 6*/
            if (i < j)              /* 7*/
                Swap(&A[i], &A[j]); /* 8*/
            else
                break; /* 9*/
        }
        Swap(&A[i], &A[Right - 1]); /*10*/ /* Restore pivot */

        if (k <= i)                      /*11*/
            Qselect(A, k, Left, i - 1);  /*12*/
        else if (k > i + 1)              /*13*/
            Qselect(A, k, i + 1, Right); /*14*/
    }
    else                                           /* Do an insertion sort on the subarray */
        InsertionSort(A + Left, Right - Left + 1); /*15*/
}
/* END */

/* ROUTINES TO TEST THE SORTS */

void Permute(ElementType A[], int N)
{
    int i;

    for (i = 0; i < N; i++)
        A[i] = i;
    for (i = 1; i < N; i++)
        Swap(&A[i], &A[rand() % (i + 1)]);
}

void Checksort(ElementType A[], int N)
{
    int i;
    for (i = 0; i < N; i++)
        if (A[i] != i)
            printf("Sort fails: %d %d\n", i, A[i]);
    printf("Check completed\n");
}

void Copy(ElementType Lhs[], const ElementType Rhs[], int N)
{
    int i;
    for (i = 0; i < N; i++)
        Lhs[i] = Rhs[i];
}

#define MaxSize 7000
int Arr1[MaxSize];
int Arr2[MaxSize];

main()
{
    int i;

    for (i = 0; i < 10; i++)
    {
        Permute(Arr2, MaxSize);
        Copy(Arr1, Arr2, MaxSize);
        InsertionSort(Arr1, MaxSize);
        Checksort(Arr1, MaxSize);

        Copy(Arr1, Arr2, MaxSize);
        Shellsort(Arr1, MaxSize);
        Checksort(Arr1, MaxSize);

        Copy(Arr1, Arr2, MaxSize);
        Heapsort(Arr1, MaxSize);
        Checksort(Arr1, MaxSize);

        Copy(Arr1, Arr2, MaxSize);
        Mergesort(Arr1, MaxSize);
        Checksort(Arr1, MaxSize);

        Copy(Arr1, Arr2, MaxSize);
        Quicksort(Arr1, MaxSize);
        Checksort(Arr1, MaxSize);

        Copy(Arr1, Arr2, MaxSize);
        Qselect(Arr1, MaxSize / 2 + 1 + i, 0, MaxSize - 1);
        if (Arr1[MaxSize / 2 + i] != MaxSize / 2 + i)
            printf("Select error: %d %d\n", MaxSize / 2 + i,
                   Arr1[MaxSize / 2 + i]);
        else
            printf("Select works\n");
    }

    return 0;
}
