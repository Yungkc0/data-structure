#include "all.h"

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

const int N = 10;
int main()
{
    int a[N];

    CREATE_ARRAY(a, N, N);
    PRINT_ARRAY(a, N);
    insertionSort(a, N);
    PRINT_ARRAY(a, N);

    return 0;
}
