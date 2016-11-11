#include "all.h"

void selectionSort(int a[], int n)
{
    int min_index;
    for (int i = 0; i < n - 1; ++i) {
        min_index = i;
        for (int j = i + 1; j < n; ++j) {
            if (a[min_index] > a[j])
                SWAP(a[min_index], a[j]);
        }
    }
}

const int N = 10;
int main()
{
    int a[N];

    CREATE_ARRAY(a, N, N);
    PRINT_ARRAY(a, N);
    selectionSort(a, N);
    PRINT_ARRAY(a, N);

    return 0;
}
