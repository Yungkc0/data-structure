#include <stdio.h>
#include <ctype.h>
#include <string.h>

void encrypt(const char *p, const int key[][3], char *c);

int main() {
    const int key[][3] = {
        {17, 17, 5},
        {21, 18, 21},
        {2, 2, 19}
    };
    const char *p = "pay more money";
    char c[strlen(p) + (3-strlen(p)%3) + 1];

    memset(c, 0, sizeof(c));

    printf("p: %s\n", p);
    encrypt(p, key, c);
    printf("Encrypted: %s\n", c);

    return 0;
}

void encrypt(const char *p, const int key[][3], char *c) {
    size_t plen = strlen(p);
    size_t pplen = plen;
    char pp[pplen];

    pplen = 0;
    for (size_t i = 0; i < plen; i++) {
        if (p[i] == ' ')
            continue;
        pp[pplen++] = toupper(p[i]);
    }

    int m = 0;
    for (size_t pi = 0; pi < pplen/3; pi++) {
        for (int i = 0; i < 3; i++) {
            c[m] = 0;
            for (int j = 0; j < 3; j++)
                c[m] += (pp[pi*3+j]-'A') * key[i][j];
            if (c[m] < 0)
                c[m] += 26 - c[m] + 26;
            c[m] = c[m]%26 + 'A';
            m++;
        }
    }
}
