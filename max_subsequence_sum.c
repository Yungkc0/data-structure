#include <stdio.h>

#define N(Array) (int)(sizeof(Array) / sizeof(Array[0]))

/* O(N^3) */
int maxsubsum_1(int a[], int n)
{
	int i, j, k, maxsum, thissum;

	maxsum = 0;
	for (i = 0; i < n; ++i) {
		for (j = i; j < n; ++j) {
			thissum = 0;
			for (k = i; k < j + 1; ++k)
				thissum += a[k];
			if (thissum > maxsum)
				maxsum = thissum;
		}
	}

	return maxsum;
}

/* O(N^2) */
int maxsubsum_2(int a[], int n)
{
	int i, j, maxsum, thissum;

	maxsum = 0;
	for (i = 0; i < n; ++i) {
		thissum = 0;
		for (j = 1; j < n; ++j) {
			thissum += a[j];
			if (thissum > maxsum)
				maxsum = thissum;
		}
	}

	return maxsum;
}

/* O(N * logN) */
int maxsubsum_3(int a[], int start, int end)
{
	int i, mid, lmax, rmax, tmpmax, mmax, thissum;

	if (start == end) {
		if (a[start] < 0) {
			return 0;
		} else {
			return a[start];
		}
	}

	mid = (start + end) / 2;
	lmax = maxsubsum_3(a, start, mid);
	rmax = maxsubsum_3(a, mid + 1, end);

	mmax = thissum = tmpmax = 0;
	for (i = mid; i >= start; --i) {
		thissum += a[i];
		if (thissum > tmpmax)
			tmpmax = thissum;
	}
	mmax += tmpmax;
	thissum = tmpmax = 0;
	for (i = mid + 1; i < end; ++i) {
		thissum += a[i];
		if (thissum > tmpmax)
			tmpmax = thissum;
	}
	mmax += tmpmax;

	if (lmax >= rmax) {
		if (lmax >= mmax) {
			return lmax;
		} else {
			return mmax;
		}
	} else if (rmax >= mmax) {
		return rmax;
	} else {
		return mmax;
	}
}

/* O(N) */
int maxsubsum_4(int a[], int n)
{
	int i, thissum, maxsum;

	thissum = maxsum = 0;
	for (i = 0; i < n; ++i) {
		thissum += a[i];

		if (thissum > maxsum)
			maxsum = thissum;
		else if (thissum < 0)
			thissum = 0;
	}

	return maxsum;
}

int main()
{
	int maxsum;
	int nums[] = {10, -23, 54, 20, -12, -65, 44, 24, 12, 95 , -45};

	maxsum = maxsubsum_4(nums, N(nums));
	printf("Max sub sum is: %d\n", maxsum);

	return 0;
}
