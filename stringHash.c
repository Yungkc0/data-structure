#include "all.h"

unsigned SDBMHash(char *str) {
    unsigned hash = 0;
    while (*str)
        hash = (*str++) + (hash << 6) + (hash << 16) - hash;
    return (hash & 0x7fffffff);
}

unsigned RSHash(char *str) {
    unsigned b = 378551;
    unsigned a = 63689;
    unsigned hash = 0;
    while (*str) {
        hash = hash*a + (*str++);
        a *= b;
    }
    return (hash & 0x7fffffff);
}

unsigned JSHash(char *str) {
    unsigned hash = 1315423911;
    while (*str)
        hash ^= ((hash << 5) + (*str++) + (hash >> 2));
    return (hash & 0x7fffffff);
}

unsigned PJWHash(char *str) {
    unsigned bitsInUnsigned = sizeof(unsigned) * 8;
    unsigned threeQuarters = (bitsInUnsigned*3) / 4;
    unsigned oneEighth = bitsInUnsigned / 8;
    unsigned highBits = 0xffffffff << (bitsInUnsigned - oneEighth);
    unsigned hash = 0;
    unsigned test = 0;

    while (*str) {
        hash = (hash << oneEighth) + (*str++);
        if ((test = hash & highBits) != 0)
            hash = (hash ^ (test >> threeQuarters)) & (~highBits);
    }
    return (hash & 0x7fffffff);
}

unsigned ELFHash(char *str) {
    unsigned hash = 0;
    unsigned x = 0;
    while (*str) {
        hash = (hash << 4) + (*str++);
        if ((x = hash & 0xf0000000L) != 0) {
            hash ^= (x >> 24);
            hash &= ~x;
        }
    }
    return (hash & 0x7fffffff);
}

// The best.
unsigned BKDRHash(char *str) {
    unsigned seed = 131; // 31 131 1313 13131 etc...
    unsigned hash = 0;
    while (*str)
        hash = hash*seed + (*str++);
    return (hash & 0x7fffffff);
}

unsigned DJBHash(char *str) {
    unsigned hash = 5381;
    while (*str)
        hash += (hash << 5) + (*str++);
    return (hash & 0x7fffffff);
}

unsigned APHash(char *str) {
    unsigned hash = 0;
    for (int i = 0; *str; i++) {
        if ((i & 1) == 0)
            hash ^= (hash << 7) ^ (*str++) ^ (hash >> 3);
        else
            hash ^= ~((hash << 11) ^ (*str++) ^ (hash >> 5));
    }
    return (hash & 0x7fffffff);
}

int main() {
    char *str = "Hello, world!\n";
    printf("%#010x\n%#010x\n%#010x\n%#010x\n%#010x\n%#010x\n%#010x\n%#010x\n",
            APHash(str), DJBHash(str), BKDRHash(str), ELFHash(str),
            SDBMHash(str), JSHash(str), PJWHash(str), RSHash(str));

    return 0;
}
