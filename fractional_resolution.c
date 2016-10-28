/* input k, find integer x≥y to 1/k=1/x+1/y */

#include "all.h"

int isInt(double x)
{
    if (x == (int) x)
        return 1;
    else
        return 0;
}

int main()
{
    double k, x, y;

    scanf("%lf", &k);
    for (y = 1; y <= 2*k; ++y) {
        x = (k*y)/(y-k);
        if (x >= y && isInt(x))
            printf("1/%.0lf = 1/%.0lf + 1/%.0lf\n", k, x, y);
        else
            continue;
    }

    return 0;
}
