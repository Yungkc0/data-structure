#include <stdio.h>
#include <ctype.h>
#include <string.h>

#define PAYLOAD 'Q'

struct AlphaHahTable {
    int row;
    int col;
} aht[26];

int am[5][5];

void initAlphaTable();
void encrypt(const char *p, char *c);
void decrypt(const char *c, char *p);

int main() {
    const char *p = "Playfair cipher was actually invented by wheatstone";
    const char *key = "fivestars";
    // 1 for '\0'.
    char c[strlen(p) + (strlen(p) % 2) + 1];
    char dep[sizeof(c)];

    initAlphaTable(key);

    memset(c, 0, sizeof(c));
    memset(dep, 0, sizeof(dep));
    for (int i = 0; i < 5; i++) {
        for (int j = 0; j < 5; j++) {
            printf("%2c", am[i][j] + 'A');
        }
        putchar('\n');
    }
    putchar('\n');

    printf("p: %s\n", p);
    encrypt(p, c);
    printf("Encrypted: %s\n", c);
    decrypt(c, dep);
    printf("Decrypted: %s\n", dep);

    return 0;
}

int alphaHash(int ch) {
    ch = toupper(ch);
    if (ch == 'J')
        ch = 'I';
    return ch - 'A';
}

void initAlphaTable(const char *key) {
    int row = 1, col = 1;

    memset(aht, 0, sizeof(aht));

    for (unsigned i = 0; i < strlen(key); i++) {
        int h = alphaHash(key[i]);
        if (aht[h].row != 0)
            continue;
        aht[h].col = col;
        aht[h].row = row;
        if (col == 5) {
            col = 1;
            row++;
        } else {
            col++;
        }
    }
    for (int i = 0; i < 26; i++) {
        int h = alphaHash(i + 'A');
        if (aht[h].row != 0)
            continue;
        aht[h].row = row;
        aht[h].col = col;
        if (col == 5) {
            col = 1;
            row++;
        } else {
            col++;
        }
    }

    for (int i = 0; i < 26; i++) {
        if (i+'A' == 'J')
            continue;
        am[aht[i].row-1][aht[i].col-1] = i;
    }
}

void encrypt(const char *p, char *c) {
    size_t plen = strlen(p);
    size_t pplen = plen + plen%2;
    char pp[plen + plen % 2 + 1];

    pplen = 0;
    for (size_t i = 0; i < plen; i++) {
        if (p[i] == ' ')
            continue;
        pp[pplen++] = p[i];
    }
    if (pplen % 2 != 0)
        pp[pplen++] = PAYLOAD;
    pp[pplen] = '\0';

    for (size_t i = 0; i < pplen;) {
        if (pp[i] == ' ') {
            c[i++] = ' ';
            continue;
        }
        int h1 = alphaHash(pp[i]);
        int h2 = alphaHash(pp[i+1]);
        int c1, c2;

        if (aht[h1].row == aht[h2].row) {
            c1 = am[aht[h1].row-1][aht[h1].col%5];
            c2 = am[aht[h2].row-1][aht[h2].col%5];
        } else if (aht[h1].col == aht[h2].col) {
            c1 = am[aht[h1].row%5][aht[h1].col-1];
            c2 = am[aht[h2].row%5][aht[h2].col-1];
        } else {
            if (aht[h1].col > aht[h2].col) {
                c1 = am[aht[h1].row-1][aht[h2].col-1];
                c2 = am[aht[h2].row-1][aht[h1].col-1];
            } else {
                c1 = am[aht[h1].row-1][aht[h2].col-1];
                c2 = am[aht[h2].row-1][aht[h1].col-1];
            }
        }
        c[i] = c1 + 'A';
        c[i+1] = c2 + 'A';

        i += 2;
    }
}

int getColOrRow(int rc) {
    rc -= 1;
    return rc == 0 ? 5 : rc;
}

void decrypt(const char *c, char *p) {
    size_t clen = strlen(c);
    p[clen] = '\0';
    for (size_t i = 0; i < clen;) {
        if (c[i] == ' ') {
            p[i++] = ' ';
            continue;
        }
        int h1 = alphaHash(c[i]);
        int h2 = alphaHash(c[i+1]);
        int p1, p2;

        if (aht[h1].row == aht[h2].row) {
            p1 = am[aht[h1].row-1][getColOrRow(aht[h1].col)-1];
            p2 = am[aht[h2].row-1][getColOrRow(aht[h2].col)-1];
        } else if (aht[h1].col == aht[h2].col) {
            p1 = am[getColOrRow(aht[h1].row)-1][aht[h1].col-1];
            p2 = am[getColOrRow(aht[h2].row)-1][aht[h2].col-1];
        } else {
            if (aht[h1].col > aht[h2].col) {
                p1 = am[aht[h1].row-1][aht[h2].col-1];
                p2 = am[aht[h2].row-1][aht[h1].col-1];
            } else {
                p1 = am[aht[h1].row-1][aht[h2].col-1];
                p2 = am[aht[h2].row-1][aht[h1].col-1];
            }
        }
        p[i] = p1 + 'A';
        p[i+1] = p2 + 'A';

        i += 2;
    }
}
