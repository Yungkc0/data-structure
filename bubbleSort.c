#include "all.h"

void bubbleSort(int a[], int n)
{
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n - i - 1; ++j) {
            if (a[j] > a[j + 1])
                SWAP(a[j], a[j + 1]);
        }
    }
}

const int N = 10;
int main()
{
    int a[N];

    CREATE_ARRAY(a, N, N);
    PRINT_ARRAY(a, N);
    bubbleSort(a, N);
    PRINT_ARRAY(a, N);

    return 0;
}
