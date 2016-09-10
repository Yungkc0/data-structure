/* bucket sort, O(MAXVALUE + ARRSIZE) */

#include "all.h"

#define MAXVALUE 999
#define ARRSIZE  10

int main()
{
	int count[MAXVALUE], i;
	int array[10] = {64, 8, 216, 512, 27, 729, 0, 1, 343, 125};

	memset(count, 0, MAXVALUE * sizeof(int));
	for (i = 0; i < ARRSIZE; ++i)
		count[array[i]] = 1;
	for (i = 0; i < MAXVALUE; ++i)
		if (count[i] == 1)
			printf("%-4d", i);
	putchar('\n');

	return 0;
}
