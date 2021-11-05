#include"countsort.h"

void CountSortTest()
{
    int a[] = { 9,5,2,3,7,6,0,6,9,4,0,6,4,7,8,1 };
	PrintArray(a, sizeof(a) / sizeof(int));
	CountSort(a, sizeof(a) / sizeof(int));
	printf("CountSort:");
	PrintArray(a, sizeof(a) / sizeof(int));
}
int main()
{
    CountSortTest();
    return 0;
}
