/* abcde/fghij=n, 2≤n≤79 */

#include "all.h"

int isOk(int n)
{
    int i, a[10] = {0};

    for (; n > 0; n /= 10)
        a[n % 10]++;
    for (i = 0; i < 10; ++i)
        if (a[i] > 1)
            return 0;
    return 1;
}

int isOk2(int _a, int _b)
{
    int i, a[10] = {0};
    int n = _a, m = _b;

    for (; n > 0; n /= 10)
        a[n % 10]++;
    for (; m > 0; m /= 10)
        a[m % 10]++;
    for (i = 1; i < 10; ++i)
        if (a[i] != 1)
            return 0;
    return 1;
}

int main()
{
    int n, i, m;

    scanf("%d", &n);
    for (i = 1234; i < 98765; ++i) {
        if (isOk(i))
            ;
        else
            continue;
        m = i * n;
        if (m <= 98765 && isOk2(m, i))
            printf("%d/%d=%d\n", m, i, n);
        else
            continue;
    }

    return 0;
}
