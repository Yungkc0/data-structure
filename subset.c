#include "all.h"

/* 1024 nodes */
void print_subset1(int n, int *a, int cur)
{
    int i, s;
    for (i = 0; i < cur; ++i)
        printf("%3d", a[i]);
    putchar('\n');
    s = cur ? a[cur - 1] + 1 : 0;
    for (i = s; i < n; ++i) {
        a[cur] = i;
        print_subset1(n, a, cur + 1);
    }
}

/* 2047 nodes */
void print_subset2(int n, int *b, int cur)
{
    int i;
    if (cur == n) {
        for (i = 0; i < cur; ++i)
            if (b[i])
                printf("%3d", i);
        putchar('\n');
        return;
    }
    b[cur] = 1;
    print_subset2(n, b, cur + 1);
    b[cur] = 0;
    print_subset2(n, b, cur + 1);
}

/* O(2^n * n) */
void print_subset3(int n)
{
    int i, j;
    for (i = 0; i < (1 << n); ++i) {
        for (j = 0; j < n; ++j)
            if (i & (1 << j))
                printf("%3d", j);
        putchar('\n');
    }
}

int main()
{
    const int n = 5;
    print_subset3(n);
    return 0;
}
