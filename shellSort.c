#include "all.h"

void shellSort(int a[], int n)
{
    int tmp;
    for (int gap = n >> 1; gap > 0; gap >>= 1) {
        for (int i = gap; i < n; ++i) {
            tmp = a[i];
            int j = i - gap;
            for (; j >= 0 && a[j] > tmp; j -= gap) {
                a[j + gap] = a[j];
            }
            a[j + gap] = tmp;
        }
    }
}

const int N = 30;
int main()
{
    int a[N];
    CREATE_ARRAY(a, N, N);
    PRINT_ARRAY(a, N);
    shellSort(a, N);
    PRINT_ARRAY(a, N);

    return 0;
}
