#include "all.h"

#define MAX          10
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

    H = malloc(sizeof(struct HeapStruct));
    H->Elements = malloc(sizeof(ElementType) * (MaxElements + 1));
    H->Size = 0;
    H->Capacity = MaxElements;
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
        Error("Heap is Full!!");
        return;
    }
    for (i = ++H->Size; H->Elements[i / 2] > X; i /= 2)
        H->Elements[i] = H->Elements[i / 2];
    H->Elements[i] = X;
}

static void PercolateDown(PriorityQueue H, int index)
{
    ElementType Child;

    for (int i = index; i * 2 <= H->Size; i = Child) {
        Child = i * 2;
        if (Child < H->Size && H->Elements[Child] > H->Elements[Child + 1])
            ++Child;
        if (H->Elements[i] > H->Elements[Child])
            SWAP(H->Elements[i], H->Elements[Child]);
        else
            break;
    }
}

/* O(N) */
void BuildHeap(PriorityQueue H, int Arr[], int N)
{
    for (int i = 1; i <= N; ++i)
        H->Elements[++H->Size] = Arr[i - 1];
    for (int i = N / 2; i > 0; --i)
        PercolateDown(H, i);
}

ElementType DeleteMin(PriorityQueue H)
{
    ElementType MinElement, LastElement;
    int Child, i;

    if (IsEmpty(H)) {
        Error("Heap is Empty!!");
        return -1;
    }
    MinElement  = H->Elements[1];
    LastElement = H->Elements[H->Size--];
    for (i = 1; i * 2 < H->Size; i = Child) {
        Child = i * 2;
        /* Find smaller child. */
        if (H->Elements[Child + 1] < H->Elements[Child] && Child != H->Size)
            ++Child;
        if (H->Elements[Child] >= LastElement)
            break;
        else
            H->Elements[i] = H->Elements[Child];
    }
    H->Elements[i] = LastElement;
    return MinElement;
}

void Display(PriorityQueue H)
{
    for (int i = 1; i < H->Size + 1; ++i)
        printf("%3d", H->Elements[i]);
    putchar('\n');
}

int main()
{
    int i;
    ElementType a[MAX];

    CREATE_ARRAY(a, MAX, 100);
    PriorityQueue H = Initialize(MAX);
    PriorityQueue Q = Initialize(MAX);
    BuildHeap(Q, a, MAX);
    for (i = 0; i < MAX; ++i)
        Insert(a[i], H);
    Display(H);
    Display(Q);
#if 0
    DeleteMin(H);
    Display(H);
#endif

    return 0;
}
