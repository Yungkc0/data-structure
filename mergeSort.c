#include "all.h"

void merge(int a[], int tmp[], int lPos, int rPos, int rEnd)
{
    int lEnd = rPos - 1;
    int cur  = lPos;
    int len  = rEnd - lPos + 1;
    while (lPos <= lEnd && rPos <= rEnd) {
        if (a[lPos] <= a[rPos])
            tmp[cur++] = a[lPos++];
        else
            tmp[cur++] = a[rPos++];
    }
    while (lPos <= lEnd)
        tmp[cur++] = a[lPos++];
    while (rPos <= rEnd)
        tmp[cur++] = a[rPos++];
    for (int i = 0; i < len; ++i, --rEnd)
        a[rEnd] = tmp[rEnd];
}

void mSort(int a[], int tmp[], int left, int right)
{
    if (left < right) {
        int center = (left + right) / 2;
        mSort(a, tmp, left, center);
        mSort(a, tmp, center + 1, right);
        merge(a, tmp, left, center + 1, right);
    }
}

void mergeSort(int a[], int n)
{
    int *tmpArray = malloc(sizeof(int) * n);
    mSort(a, tmpArray, 0, n - 1);
    free(tmpArray);
}

const int N = 10;
int main()
{
    int a[N];

    CREATE_ARRAY(a, N, N);
    PRINT_ARRAY(a, N);
    mergeSort(a, N);
    PRINT_ARRAY(a, N);

    return 0;
}
