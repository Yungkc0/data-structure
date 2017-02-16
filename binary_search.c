#include "all.h"

int binsearch(int x, int v[], int n) {
    int low, high, mid;

    low = 0;
    high = n - 1;
    while (low <= high) {
        mid = low + (high - low) / 2;
        if (x < v[mid])
            high = mid - 1;
        else if (x > v[mid])
            low = mid + 1;
        else
            return mid;
    }
    return -1;
}

int cmp_int(const void *a, const void *b) {
    return *(int*)a > *(int*)b;
}

int main() {
    const int n = 10;
    const int ntests = 100;
    int a[n];
    int x, res;

    srand(time(NULL));
    for (int i = 0; i < ntests; ++i) {
        CREATE_ARRAY(a, n, 100);
        x = a[5];
        qsort(a, n, sizeof(int), cmp_int);
        PRINT_ARRAY(a, n);
        printf("Finding: %d\n", x);
        if ((res = binsearch(x, a, n)) != -1) {
            printf("Found: a[%d] => %d\n", res, a[res]);
        } else {
            puts("Not Found");
        }
    }
}
