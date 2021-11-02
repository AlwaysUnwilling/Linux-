#include"qsnonr.h"


void QuickSortNonRTest() 
{
	int a[] = { 9,5,2,3,7,6,21,6,42,4,0,6,4,7,8,1 };
	PrintArray(a, sizeof(a) / sizeof(int));
	QuickSortNonR(a, 0, sizeof(a) / sizeof(int) - 1);
	printf("QuickSortNonR:");
	PrintArray(a, sizeof(a) / sizeof(int));
}
int main()
{
    QuickSortNonRTest();
    return 0;
}
