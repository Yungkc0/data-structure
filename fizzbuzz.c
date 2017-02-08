#include "all.h"

void fizzBuzz(int n) {
    for (int i = 1; i <= n; ++i) {
        if (i % 3 && i % 5) {
            printf("%d", i);
        } else {
            if (i % 3 == 0)
                printf("Fizz");
            if (i % 5 == 0)
                printf("Buzz");
        }
        puts("");
    }
}

int main() {
    int n;

    printf("Input n: ");
    scanf("%d", &n);
    fizzBuzz(n);
}
