#include "all.h"

void stringZip(char *s, size_t len, char *t)
{
    int cnt = 1, j;

    j = 0;
    for (size_t i = 0; i < len; ++i) {
        if (s[i] == s[i + 1]) {
            ++cnt;
        } else {
            if (cnt > 1) {
                int pow = 1;
                int tmp = cnt;
                while (tmp > 0) {
                    tmp /= 10;
                    pow *= 10;
                }
                pow /= 10;
                while (pow > 0) {
                    int c = cnt / pow + '0';
                    t[j++] = c;
                    cnt %= pow;
                    pow /= 10;
                }
            }
            t[j++] = s[i];
            cnt = 1;
        }
    }
    t[j] = 0;
}

int main(int argc, char **argv)
{
    if (argc != 2)
        exit(1);
    size_t len = strlen(argv[1]);
    char t[len];
    stringZip(argv[1], len, t);
    puts(t);
    return 0;
}
