#include "all.h"

int lowerBound(int nums[], int target, int len)
{
    int lb = 0, ub = len - 1;
    while (lb + 1 < ub) {
        int mid = (lb + ub) / 2;
        if (nums[mid] < target) {
            lb = mid;
        } else {
            ub = mid;
        }
    }
    if (nums[lb + 1] == target)
        return lb + 1;
    else
        return -1;
}

int upperBound(int nums[], int target, int len)
{
    int lb = 0, ub = len - 1;
    while (lb + 1 < ub) {
        int mid = (ub + lb) / 2;
        if (nums[mid] > target) {
            ub = mid;
        } else {
            lb = mid;
        }
    }
    if (nums[ub - 1] == target)
        return ub - 1;
    else
        return -1;
}

int main()
{
    int nums[] = {1, 2, 2, 3, 4, 6, 6, 7, 8, 18};

    printf("lowerBound: %d\n", lowerBound(nums, 6, ARRAY_LENGTH(nums)));
    printf("upperBound: %d\n", upperBound(nums, 6, ARRAY_LENGTH(nums)));
    printf("lowerBound: %d\n", lowerBound(nums, 7, ARRAY_LENGTH(nums)));
    printf("upperBound: %d\n", upperBound(nums, 7, ARRAY_LENGTH(nums)));

    return 0;
}
