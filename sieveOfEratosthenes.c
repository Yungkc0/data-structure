#include "all.h"

static int* primers;
static int  primerLen = 0;

void E(int n);
void printPrimers(void);

int main() {
    int n;

    printf("Input n: ");
    scanf("%d", &n);
    if (n < 0) {
        fprintf(stderr, "Error: n is must bigger than 0!\n");
        exit(1);
    }
    primers = malloc(n * sizeof(int));
    if (primers == NULL) {
        fprintf(stderr, "Error: malloc failed!\n");
        exit(1);
    }
    E(n);
    printf("There are %d primers less than %d: ", primerLen, n);
    printPrimers();

    return 0;
}

void E(int n) {
    if (n < 2)
        return;
    primers[primerLen++] = 2;
    for (int i = 3; i <= n; ++i) {
        int sign = 1;
        int sq = (int)sqrt(i);
        for (int j = 0; primers[j] <= sq && j < primerLen; ++j) {
            if (i % primers[j] == 0) {
                sign = 0;
                break;
            }
        }
        if (sign)
            primers[primerLen++] = i;
    }
}

void printPrimers() {
    for (int i = 0; i < primerLen; ++i) {
        if (i == 0)
            printf("%d", primers[i]);
        else
            printf(" %d", primers[i]);
    }
    printf("\nA total of %d\n", primerLen);
}
