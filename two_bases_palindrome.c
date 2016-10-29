#include "all.h"

void baseConversion(char *s, int n, int base)
{
    int i;

    for (i = 0; n != 0; ++i, n /= base)
        s[i] = n % base + '0';
}

int isPalindrome(const char *s)
{
    size_t len, i, j;

    len = strlen(s);
    if (len % 2 == 0)
        j = len / 2;
    else
        j = len / 2 + 1;
    i = len / 2 - 1;
    for (; s[j] != 0; --i, ++j) {
        if (s[i] != s[j])
            return 0;
    }
    return 1;
}

int main()
{
    int n, base, sign;
    char s[30] = {0};

    scanf("%d", &n);
    for (++n; ; ++n) {
        sign = 0;
        for (base = 2; base <= 10; ++base) {
            memset(s, 0, 30);
            baseConversion(s, n, base);
            if (isPalindrome(s))
                if (++sign >= 2)
                    break;
        }
        if (sign >= 2) {
            printf("%d\n", n);
            break;
        }
    }

    return 0;
}
