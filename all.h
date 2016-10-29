#ifndef ALL_H
#	define ALL_H

#include <math.h>
#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define max(a, b)         ((a) > (b) ? (a) : (b))
#define Error(format, ...)  fprintf(stderr, format "\n", ##__VA_ARGS__)
#define FatalError(format, ...)  do { fprintf(stderr, "Fatal error: " format "\n", ##__VA_ARGS__); exit(1); } while (0)
#define CREATE_ARRAY(a, n, max)\
    do {\
        srand(time(NULL));\
        int i = n - 1;\
        for (; i >= 0; --i)\
            a[i] = rand() % max;\
    } while (0)

#define CREATE_ORDER_ARRAY(a, n)\
    do {\
        int i;\
        for (i = 0; i < n; ++i)\
            a[i] = i + 1;\
    } while (0)

#endif
