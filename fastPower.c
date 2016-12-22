#include "all.h"

uint64_t fastModPow(uint64_t x, uint64_t n, uint64_t mod)
{
    uint64_t res = 1 % mod;
    printf("%4s %4s %4s\n", "x", "n", "res");
    while (n > 0) {
        /* if lowest bit is 1 */
        if ((n & 1) != 0)
            res = res * x % mod;
        x = x * x % mod;
        n >>= 1;
        printf("%4lu %4lu %4lu\n", x, n, res);
    }
    return res;
}

int main(int argc, char* argv[])
{
    uint64_t x, pow, mod;

    if (argc < 3)
        return 1;
    x = atol(argv[1]);
    pow = atol(argv[2]);
    if (argc < 4)
        mod = LONG_MAX;
    else
        mod = atol(argv[3]);
    printf("res = %lu\n", fastModPow(x, pow, mod));

    return 0;
}
