#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

#define PAYLOAD 'Q'

void encrypt(const char *p, const char *key, char *c);
void decrypt(const char *c, const char *key, char *p);

int main() {
    const char *key = "deceptive";
    const char *p = "We are discovered save yourself";
    char c[strlen(p) + (strlen(key) - strlen(p)%strlen(key)) + 1];
    char dep[sizeof(c)];

    memset(c, 0, sizeof(c));
    memset(dep, 0, sizeof(dep));

    printf("p: %s\n", p);
    encrypt(p, key, c);
    printf("Encrypted: %s\n", c);
    decrypt(c, key, dep);
    printf("Dncrypted: %s\n", dep);

    return 0;
}

void encrypt(const char *p, const char *key, char *c) {
    size_t klen = strlen(key);
    size_t plen = strlen(p);
    size_t pplen = strlen(p) + (strlen(key) - strlen(p)%strlen(key));
    char pp[pplen];

    pplen = 0;
    for (size_t i = 0; i < plen; i++) {
        if (p[i] == ' ')
            continue;
        pp[pplen++] = toupper(p[i]);
    }
    if (pplen % klen != 0)
        for (size_t i = 0; i < klen-(pplen%klen); i++)
            pp[pplen++] = PAYLOAD;
    pp[pplen] = '\0';


    for (size_t i = 0; i < pplen/klen; i++)
        for (size_t j = 0; j < klen; j++) {
            c[i*klen+j] = (pp[i*klen+j] - 'A' + (key[j] - 'A')) % 26 + 'A';
        }
}

void decrypt(const char *c, const char *key, char *p) {
    size_t klen = strlen(key);
    size_t clen = strlen(c);

    for (size_t i = 0; i < clen/klen; i++)
        for (size_t j = 0; j < klen; j++) {
            int tp = c[i*klen+j] - 'A' - (key[j] - 'A');
            if (tp < 0) {
                tp = 26 - abs(tp) + 26;
            }
            p[i*klen+j] = tp % 26 + 'A';
        }
}
