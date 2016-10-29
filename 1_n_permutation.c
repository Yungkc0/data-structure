#include "all.h"

void print_permutation(int n, int *a, int cur)
{
    int i, j;

    if (cur == n) {
        for (i= 0; i < n; ++i)
            printf("%3d", a[i]);
        printf("\n");
    } else for (i = 1; i <= n; ++i) {
        int ok = 1;
        for (j= 0; j < cur; ++j)
            if (a[j] == i)
                ok = 0;
        if (ok) {
            a[cur] = i;
            print_permutation(n, a, cur + 1);
        }
    }
}

int main()
{
    int n;

    scanf("%d", &n);
    int a[n];
    print_permutation(n, a, 0);

    return 0;
}
