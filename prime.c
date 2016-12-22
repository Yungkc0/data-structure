#include "all.h"

static bool isPrime(int n)
{
    for (int i = 2; i * i <= n; ++i)
        if (n % i == 0)
            return false;
    return n != 1;
}

static int primeArray(int a[], int n)
{
    int cnt = 0;

    for (int i = 0; i < n; ++i)
        if (!isPrime(a[i]))
            a[i] = 0;
        else
            cnt++;
    return cnt;
}

static int prime2toN(int n)
{
    int cnt = 0;
    for (int i = 2; i <= n; ++i)
        if (isPrime(i))
            cnt++;
    return cnt;
}

int main(int argc, char* argv[])
{
    const int MAX = 30;
    int a[MAX];

    CREATE_ARRAY(a, MAX, 100);
    PRINT_ARRAY(a, MAX);
    printf("%d prime numbers in the array:\n", primeArray(a, MAX));
    for (int i = 0; i < MAX; ++i)
        if (a[i])
            printf("%3d", a[i]);
    puts("");
    if (argc > 1)
        printf("%d prime numbers in 2~%d.\n", prime2toN(atoi(argv[1])), atoi(argv[1]));

    return 0;
}
