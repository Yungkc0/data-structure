#include "all.h"

int* gcd(int a, int b)
{
    int* res = malloc(3 * sizeof(int));
    if (b == 0) {
        res[0] = a, res[1] = 1, res[2] = 0;
        return res;
    } else {
        int* val = gcd(b, a % b);
        int d = val[0];
        int x = val[2];
        int y = val[1];
        y -= (a / b) * x;
        res[0] = d, res[1] = x, res[2] = y;
        return res;
    }
}

int* gcd2(int a, int b, int res[])
{
    if (b == 0) {
        res[0] = a, res[1] = 1, res[2] = 0;
        return res;
    } else {
        int val[3];
        gcd2(b, a % b, val);
        int d = val[0];
        int x = val[2];
        int y = val[1];
        y -= (a / b) * x;
        res[0] = d, res[1] = x, res[2] = y;
        return res;
    }
}

int main(int argc, char* argv[])
{
    int res[3];

    gcd2(atoi(argv[1]), atoi(argv[2]), res);
    printf("res: d = %d, x = %d, y = %d\n", res[0], res[1], res[2]);

    return 0;
}
