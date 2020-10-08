#include "fatal.h"
#include "hashquad.h"
#include <stdlib.h>

#define MinTableSize (10)

enum KindOfEntry
{
    Legitimate,
    Empty,
    Deleted
};

struct HashEntry
{
    ElementType Element;
    enum KindOfEntry Info;
};

typedef struct HashEntry Cell;

/* Cell *TheCells will be an array of */
/* HashEntry cells, allocated later */
struct HashTbl
{
    int TableSize;
    Cell *TheCells;
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

/* START: fig5_15.txt */
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

    /* Allocate array of Cells */
    H->TheCells = malloc(sizeof(Cell) * H->TableSize); /* 8*/
    if (H->TheCells == NULL)                           /* 9*/
        FatalError("Out of space!!!");                 /*10*/

    for (i = 0; i < H->TableSize; i++) /*11*/
        H->TheCells[i].Info = Empty;   /*12*/

    return H; /*13*/
}
/* END */

/* START: fig5_16.txt */
Position
Find(ElementType Key, HashTable H)
{
    Position CurrentPos;
    int CollisionNum;

    CollisionNum = 0;                               /* 1*/
    CurrentPos = Hash(Key, H->TableSize);           /* 2*/
    while (H->TheCells[CurrentPos].Info != Empty && /* 3*/
           H->TheCells[CurrentPos].Element != Key)
    /* Probably need strcmp!! */
    {
        CurrentPos += 2 * ++CollisionNum - 1; /* 4*/
        if (CurrentPos >= H->TableSize)       /* 5*/
            CurrentPos -= H->TableSize;       /* 6*/
    }
    return CurrentPos; /* 7*/
}
/* END */

/* START: fig5_17.txt */
void Insert(ElementType Key, HashTable H)
{
    Position Pos;

    Pos = Find(Key, H);
    if (H->TheCells[Pos].Info != Legitimate)
    {
        /* OK to insert here */
        H->TheCells[Pos].Info = Legitimate;
        H->TheCells[Pos].Element = Key;
        /* Probably need strcpy! */
    }
}
/* END */

/* START: fig5_22.txt */
HashTable
Rehash(HashTable H)
{
    int i, OldSize;
    Cell *OldCells;

    OldCells = H->TheCells; /* 1*/
    OldSize = H->TableSize; /* 2*/

    /* Get a new, empty table */
    H = InitializeTable(2 * OldSize); /* 3*/

    /* Scan through old table, reinserting into new */
    for (i = 0; i < OldSize; i++)           /* 4*/
        if (OldCells[i].Info == Legitimate) /* 5*/
            Insert(OldCells[i].Element, H); /* 6*/

    free(OldCells); /* 7*/

    return H; /* 8*/
}
/* END */

ElementType
Retrieve(Position P, HashTable H)
{
    return H->TheCells[P].Element;
}

void DestroyTable(HashTable H)
{
    free(H->TheCells);
    free(H);
}
