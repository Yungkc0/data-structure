#include "all.h"

void percDown(int a[], int index, int n)
{
    int i, child;

    i = index;
    for (; i*2 + 1 < n - 1; i = child) {
        child = i*2 + 1;
        if (child < n - 1 && a[child + 1] > a[child])
            ++child;
        if (a[i] < a[child])
            SWAP(a[i], a[child]);
        else
            break;
    }
}

void heapSort(int a[], int n)
{
    for (int i = n / 2; i >= 0; --i)
        percDown(a, i, n);
    for (int i = n - 1; i >= 0; --i) {
        SWAP(a[i], a[0]);
        percDown(a, 0, i);
    }
}

const int N = 10;
int main()
{
    int a[N];
    CREATE_ARRAY(a, N, N * 10);
    PRINT_ARRAY(a, N);
    heapSort(a, N);
    PRINT_ARRAY(a, N);

    return 0;
}
