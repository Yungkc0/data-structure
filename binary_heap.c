#include "all.h"

#define MAX          100
#define MinPQSize    0
#define MinData      0
#define ElementType  int

struct HeapStruct;
typedef struct HeapStruct *PriorityQueue;

struct HeapStruct {
    int Capacity;
    int Size;
    ElementType *Elements;
};

PriorityQueue Initialize(int MaxElements)
{
    PriorityQueue H;
 
    if (MaxElements < MinPQSize)
        FatalError("Priority queue size is too small");
    H = malloc(sizeof(struct HeapStruct));
    if (H == NULL)
        FatalError("malloc error: Out of memory!");
    H->Elements = malloc((MaxElements + 1) * sizeof(ElementType));
    if (H->Elements == NULL)
        FatalError("malloc error: Out of memory!");
    H->Capacity = MaxElements;
    H->Size = 0;
    H->Elements[0] = MinData;

    return H;
}

int IsFull(PriorityQueue H)
{
    return (H->Size == H->Capacity);
}

int IsEmpty(PriorityQueue H)
{
    return (H->Size == 0);
}

void Insert(ElementType X, PriorityQueue H)
{
    int i;

    if (IsFull(H)) {
        Error("Priority queue is full");
        return;
    }
    for (i = ++H->Size; H->Elements[i/2] > X; i /= 2)
        H->Elements[i] = H->Elements[i/2];
    H->Elements[i] = X;
}

ElementType DeleteMin(PriorityQueue H)
{
    int i, Child;
    ElementType MinElement, LastElement;

    if (IsEmpty(H)) {
        Error("Priority queue is empty");
        return H->Elements[0];
    }
    MinElement = H->Elements[1];
    LastElement = H->Elements[H->Size--];

    for (i = 1; i*2 <= H->Size; i = Child) {
        Child = i*2;
        if (Child != H->Size && H->Elements[Child + 1] < H->Elements[Child])
            Child++;
        if (LastElement > H->Elements[Child])
            H->Elements[i] = H->Elements[Child];
        else
            break;
    }
    H->Elements[i] = LastElement;
    return MinElement;
}

void Display(PriorityQueue H)
{
    int i, j, size;

    size = log2(H->Size);
    for (i = 0; i <= size; ++i)
        for (j = 0; j < pow(2, i); ++j)
            printf("%3d", H->Elements[j]);
    putchar('\n');
}

int main()
{
    int i;
    ElementType a[MAX];

    CREATE_ARRAY(a, MAX, 100);
    PriorityQueue H = Initialize(MAX);
    for (i = 0; i < MAX; ++i)
        Insert(a[i], H);
    Display(H);
    DeleteMin(H);
    Display(H);

    return 0;
}
