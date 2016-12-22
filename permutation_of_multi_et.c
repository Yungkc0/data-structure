#include "all.h"

void print_multi_set_permutation(int n, int b[], int a[], int cur)
{
    int i, j;

    if (cur == n) {
        for (i= 0; i < n; ++i)
            printf("%3d", a[i]);
        putchar('\n');
    } else for (i = 0; i < n; ++i) {
        if (!i || b[i] != b[i - 1]) {
            int c1, c2;
            c1 = c2 = 0;
            for (j= 0; j < cur; ++j)
                if (a[j] == b[i])
                    c1++;
            for (j =0; j < n; ++j)
                if (b[j] == b[i])
                    c2++;
            if (c1 < c2) {
                a[cur] = b[i];
                print_multi_set_permutation(n, b, a, cur + 1);
            }
        }
    }
}

int cmp(const void *a, const void *b)
{
    return *(int*) a - *(int*) b;
}

int main()
{
    int n;

    scanf("%d", &n);
    int a[n], b[n];
    CREATE_ARRAY(b, n, 50);
    qsort(b, n, sizeof(b[0]), cmp);
    print_multi_set_permutation(n, b, a, 0);

    return 0;
}
