#include "stackar.h"
#include "fatal.h"
#include <stdlib.h>

#define EmptyTOS (-1)
#define MinStackSize (5)

struct StackRecord
{
    int Capacity;
    int TopOfStack;
    ElementType *Array;
};

/* START: fig3_48.txt */
int IsEmpty(Stack S)
{
    return S->TopOfStack == EmptyTOS;
}
/* END */

int IsFull(Stack S)
{
    return S->TopOfStack == S->Capacity - 1;
}

/* START: fig3_46.txt */
Stack CreateStack(int MaxElements)
{
    Stack S;

    if (MaxElements < MinStackSize)       /* 1*/
        Error("Stack size is too small"); /* 2*/

    S = malloc(sizeof(struct StackRecord)); /* 3*/
    if (S == NULL)                          /* 4*/
        FatalError("Out of space!!!");      /* 5*/

    S->Array = malloc(sizeof(ElementType) * MaxElements); /* 6*/
    if (S->Array == NULL)                                 /* 7*/
        FatalError("Out of space!!!");                    /* 8*/
    S->Capacity = MaxElements;                            /* 9*/
    MakeEmpty(S);                                         /*10*/

    return S; /*11*/
}
/* END */

/* START: fig3_49.txt */
void MakeEmpty(Stack S)
{
    S->TopOfStack = EmptyTOS;
}
/* END */

/* START: fig3_47.txt */
void DisposeStack(Stack S)
{
    if (S != NULL)
    {
        free(S->Array);
        free(S);
    }
}
/* END */

/* START: fig3_50.txt */
void Push(ElementType X, Stack S)
{
    if (IsFull(S))
        Error("Full stack");
    else
        S->Array[++S->TopOfStack] = X;
}
/* END */

/* START: fig3_51.txt */
ElementType
Top(Stack S)
{
    if (!IsEmpty(S))
        return S->Array[S->TopOfStack];
    Error("Empty stack");
    return 0; /* Return value used to avoid warning */
}
/* END */

/* START: fig3_52.txt */
void Pop(Stack S)
{
    if (IsEmpty(S))
        Error("Empty stack");
    else
        S->TopOfStack--;
}
/* END */

/* START: fig3_53.txt */
ElementType
TopAndPop(Stack S)
{
    if (!IsEmpty(S))
        return S->Array[S->TopOfStack--];
    Error("Empty stack");
    return 0; /* Return value used to avoid warning */
}
/* END */
