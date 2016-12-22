#include "all.h"

#define NCARD 52

static void initCards(int cards[])
{
    int m = 0;
    for (int i = 1; i <= 13; ++i)
        for (int j = 1; j <= 4; ++j)
            cards[m++] = i == 13 ? 'K' :
                        i == 12 ? 'Q' :
                        i == 11 ? 'J' :
                        i == 10 ? '0' :
                        i == 1  ? 'A' :
                        i + '0';
}

static void printCards(int cards[])
{
    for (int i = 0; i < NCARD; ++i)
        printf("%2c", cards[i]);
    puts("");
}

static void shuffleCards(int cards[])
{
    srand(time(NULL));
    for (int i = 0; i < NCARD; ++i) {
        int k = rand() % (i + 1);
        int t = cards[i];
        cards[i] = cards[k];
        cards[k] = t;
    }
}

int main()
{
    int cards[NCARD];

    initCards(cards);
    printCards(cards);
    shuffleCards(cards);
    printCards(cards);

    return 0;
}
