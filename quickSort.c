#include "all.h"

#define CUTOFF 3

void insertionSort(int a[], int n)
{
    int tmp;
    for (int i = 1; i < n; ++i) {
        tmp = a[i];
        int j = i - 1;
        for (; j >= 0 && a[j] > tmp; --j) {
            a[j + 1] = a[j];
        }
        a[j + 1] = tmp;
    }
}

/* Use Median-of-Three Partitioning. */
int median3(int a[], int left, int right)
{
    int center = (left + right) / 2;
    if (a[left] > a[center])
        SWAP(a[left], a[center]);
    if (a[left] > a[right])
        SWAP(a[left], a[right]);
    if (a[center] > a[right])
        SWAP(a[center], a[right]);
    SWAP(a[center], a[right - 1]);
    return a[right - 1];
}

void qSort(int a[], int left, int right)
{
    int pivot, i, j;

    if (left + CUTOFF <= right) {
        pivot = median3(a, left, right);
        i = left;
        j = right - 1;
        for (; ;) {
            while (a[++i] < pivot);
            while (a[--j] > pivot);
            if (i < j)
                SWAP(a[i], a[j]);
            else
                break;
        }
        SWAP(a[i], a[right - 1]);
        qSort(a, left, i - 1);
        qSort(a, i + 1, right);
    } else {
        insertionSort(a + left, right - left + 1);
    }
}

void quickSort(int a[], int n)
{
    qSort(a, 0, n - 1);
}

const int N = 30;
int main()
{
    int a[N];

    CREATE_ARRAY(a, N, N);
    PRINT_ARRAY(a, N);
    quickSort(a, N);
    PRINT_ARRAY(a, N);

    return 0;
}
