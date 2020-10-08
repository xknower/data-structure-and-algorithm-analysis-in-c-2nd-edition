#include "binheap.h"
#include "fatal.h"
#include <stdlib.h>

#define MinPQSize (10)
#define MinData (-32767)

struct HeapStruct
{
    int Capacity;
    int Size;
    ElementType *Elements;
};

/* START: fig6_0.txt */
PriorityQueue
Initialize(int MaxElements)
{
    PriorityQueue H;

    /* 1*/ if (MaxElements < MinPQSize)
        /* 2*/ Error("Priority queue size is too small");

    /* 3*/ H = malloc(sizeof(struct HeapStruct));
    /* 4*/ if (H == NULL)
        /* 5*/ FatalError("Out of space!!!");

    /* Allocate the array plus one extra for sentinel */
    /* 6*/ H->Elements = malloc((MaxElements + 1) * sizeof(ElementType));
    /* 7*/ if (H->Elements == NULL)
        /* 8*/ FatalError("Out of space!!!");

    /* 9*/ H->Capacity = MaxElements;
    /*10*/ H->Size = 0;
    /*11*/ H->Elements[0] = MinData;

    /*12*/ return H;
}
/* END */

void MakeEmpty(PriorityQueue H)
{
    H->Size = 0;
}

/* START: fig6_8.txt */
/* H->Element[ 0 ] is a sentinel */

void Insert(ElementType X, PriorityQueue H)
{
    int i;

    if (IsFull(H))
    {
        Error("Priority queue is full");
        return;
    }

    for (i = ++H->Size; H->Elements[i / 2] > X; i /= 2)
        H->Elements[i] = H->Elements[i / 2];
    H->Elements[i] = X;
}
/* END */

/* START: fig6_12.txt */
ElementType
DeleteMin(PriorityQueue H)
{
    int i, Child;
    ElementType MinElement, LastElement;

    if (IsEmpty(H)) /* 1*/
    {
        Error("Priority queue is empty"); /* 2*/
        return H->Elements[0];            /* 3*/
    }
    MinElement = H->Elements[1];          /* 4*/
    LastElement = H->Elements[H->Size--]; /* 5*/

    for (i = 1; i * 2 <= H->Size; i = Child) /* 6*/
    {
        /* Find smaller child */
        Child = i * 2;                                 /* 7*/
        if (Child != H->Size && H->Elements[Child + 1] /* 8*/

                                    < H->Elements[Child]) /* 9*/
            Child++;                                      /*10*/

        /* Percolate one level */
        if (LastElement > H->Elements[Child])    /*11*/
            H->Elements[i] = H->Elements[Child]; /*12*/
        else
            break; /*13*/
    }
    H->Elements[i] = LastElement; /*14*/
    return MinElement;            /*15*/
}
/* END */

ElementType
FindMin(PriorityQueue H)
{
    if (!IsEmpty(H))
        return H->Elements[1];
    Error("Priority Queue is Empty");
    return H->Elements[0];
}

int IsEmpty(PriorityQueue H)
{
    return H->Size == 0;
}

int IsFull(PriorityQueue H)
{
    return H->Size == H->Capacity;
}

void Destroy(PriorityQueue H)
{
    free(H->Elements);
    free(H);
}

#if 0
/* START: fig6_14.txt */
        for( i = N / 2; i > 0; i-- )
            PercolateDown( i );
/* END */
#endif
