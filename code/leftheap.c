#include "leftheap.h"
#include "fatal.h"
#include <stdlib.h>

struct TreeNode
{
        ElementType Element;
        PriorityQueue Left;
        PriorityQueue Right;
        int Npl;
};

PriorityQueue
Initialize(void)
{
        return NULL;
}
static PriorityQueue Merge1(PriorityQueue H1, PriorityQueue H2);

/* START: fig6_26.txt */
PriorityQueue
Merge(PriorityQueue H1, PriorityQueue H2)
{
        if (H1 == NULL)                /* 1*/
                return H2;             /* 2*/
        if (H2 == NULL)                /* 3*/
                return H1;             /* 4*/
        if (H1->Element < H2->Element) /* 5*/
                return Merge1(H1, H2); /* 6*/
        else
                return Merge1(H2, H1); /* 7*/
}
/* END */

void SwapChildren(PriorityQueue H)
{
        PriorityQueue Tmp;

        Tmp = H->Left;
        H->Left = H->Right;
        H->Right = Tmp;
}

/* START: fig6_27.txt */
static PriorityQueue
Merge1(PriorityQueue H1, PriorityQueue H2)
{
        if (H1->Left == NULL) /* 1*/  /* Single node */
                H1->Left = H2; /* 2*/ /* H1->Right is already NULL,
                                       H1->Npl is already 0 */
        else
        {
                H1->Right = Merge(H1->Right, H2);   /* 3*/
                if (H1->Left->Npl < H1->Right->Npl) /* 4*/
                        SwapChildren(H1);           /* 5*/

                H1->Npl = H1->Right->Npl + 1; /* 6*/
        }
        return H1; /* 7*/
}
/* END */

/* START: fig6_29.txt */

PriorityQueue
Insert1(ElementType X, PriorityQueue H)
{
        PriorityQueue SingleNode;

        SingleNode = malloc(sizeof(struct TreeNode)); /* 1*/
        if (SingleNode == NULL)                       /* 2*/
                FatalError("Out of space!!!");        /* 3*/
        else
        {
                SingleNode->Element = X;
                SingleNode->Npl = 0;                         /* 4*/
                SingleNode->Left = SingleNode->Right = NULL; /* 5*/
                H = Merge(SingleNode, H);                    /* 6*/
        }
        return H; /* 7*/
}
/* END */

/* START: fig6_30.txt */
/* DeleteMin1 returns the new tree; */
/* To get the minimum, use FindMin */
/* This is for convenience */

PriorityQueue
DeleteMin1(PriorityQueue H)
{
        PriorityQueue LeftHeap, RightHeap;

        if (IsEmpty(H)) /* 1*/
        {
                Error("Priority queue is empty"); /* 2*/
                return H;                         /* 3*/
        }

        LeftHeap = H->Left;                /* 4*/
        RightHeap = H->Right;              /* 5*/
        free(H);                           /* 6*/
        return Merge(LeftHeap, RightHeap); /* 7*/
}
/* END */

ElementType
FindMin(PriorityQueue H)
{
        if (!IsEmpty(H))
                return H->Element;
        Error("Priority Queue is Empty");
        return 0;
}

int IsEmpty(PriorityQueue H)
{
        return H == NULL;
}
