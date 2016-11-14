#include "all.h"

#define N   10
#define MAX N*10

void countingSort(int a[], int n)
{
    int c[MAX] = {0};
    int b[N];

    for (int i = 0; i < n; ++i)
        ++c[a[i]];
    for (int i = 1; i < MAX; ++i)
        c[i] += c[i - 1];
    for (int i = n - 1; i >= 0; --i)
        b[--c[a[i]]] = a[i];
    for (int i = 0; i < n; ++i)
        a[i] = b[i];
}

int main()
{
    int a[N];

    CREATE_ARRAY(a, N, MAX);
    PRINT_ARRAY(a, N);
    countingSort(a, N);
    PRINT_ARRAY(a, N);

    return 0;
}
