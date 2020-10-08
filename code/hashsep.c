#include "fatal.h"
#include "hashsep.h"
#include <stdlib.h>

#define MinTableSize (10)

struct ListNode
{
    ElementType Element;
    Position Next;
};

typedef Position List;

/* List *TheList will be an array of lists, allocated later */
/* The lists use headers (for simplicity), */
/* though this wastes space */
struct HashTbl
{
    int TableSize;
    List *TheLists;
};

/* Return next prime; assume N >= 10 */
static int
NextPrime(int N)
{
    int i;

    if (N % 2 == 0)
        N++;
    for (;; N += 2)
    {
        for (i = 3; i * i <= N; i += 2)
            if (N % i == 0)
                goto ContOuter; /* Sorry about this! */
        return N;
    ContOuter:;
    }
}

/* Hash function for ints */
Index Hash(ElementType Key, int TableSize)
{
    return Key % TableSize;
}

/* START: fig5_8.txt */
HashTable
InitializeTable(int TableSize)
{
    HashTable H;
    int i;

    if (TableSize < MinTableSize) /* 1*/
    {
        Error("Table size too small"); /* 2*/
        return NULL;                   /* 3*/
    }

    /* Allocate table */
    H = malloc(sizeof(struct HashTbl)); /* 4*/
    if (H == NULL)                      /* 5*/
        FatalError("Out of space!!!");  /* 6*/

    H->TableSize = NextPrime(TableSize); /* 7*/

    /* Allocate array of lists */
    H->TheLists = malloc(sizeof(List) * H->TableSize); /* 8*/
    if (H->TheLists == NULL)                           /* 9*/
        FatalError("Out of space!!!");                 /*10*/

    /* Allocate list headers */
    for (i = 0; i < H->TableSize; i++) /*11*/
    {
        H->TheLists[i] = malloc(sizeof(struct ListNode)); /*12*/
        if (H->TheLists[i] == NULL)                       /*13*/
            FatalError("Out of space!!!");                /*14*/
        else
            H->TheLists[i]->Next = NULL; /*15*/
    }

    return H; /*16*/
}
/* END */

/* START: fig5_9.txt */
Position
Find(ElementType Key, HashTable H)
{
    Position P;
    List L;

    L = H->TheLists[Hash(Key, H->TableSize)]; /* 1*/
    P = L->Next;                              /* 2*/
    while (P != NULL && P->Element != Key)    /* 3*/
                                              /* Probably need strcmp!! */
        P = P->Next;                          /* 4*/
    return P;                                 /* 5*/
}
/* END */

/* START: fig5_10.txt */
void Insert(ElementType Key, HashTable H)
{
    Position Pos, NewCell;
    List L;

    Pos = Find(Key, H);     /* 1*/
    if (Pos == NULL) /* 2*/ /* Key is not found */
    {
        NewCell = malloc(sizeof(struct ListNode)); /* 3*/
        if (NewCell == NULL)                       /* 4*/
            FatalError("Out of space!!!");         /* 5*/
        else
        {
            L = H->TheLists[Hash(Key, H->TableSize)]; /* 6*/
            NewCell->Next = L->Next;                  /* 7*/
            NewCell->Element = Key; /* 8*/            /* Probably need strcpy! */
            L->Next = NewCell;                        /* 9*/
        }
    }
}
/* END */

ElementType
Retrieve(Position P)
{
    return P->Element;
}

void DestroyTable(HashTable H)
{
    int i;

    for (i = 0; i < H->TableSize; i++)
    {
        Position P = H->TheLists[i];
        Position Tmp;

        while (P != NULL)
        {
            Tmp = P->Next;
            free(P);
            P = Tmp;
        }
    }

    free(H->TheLists);
    free(H);
}
