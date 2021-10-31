#include"quicksort.h"


void QuickSortTest()
{
    int a[]={9,5,2,7,4,23,6,7,42,0,0,5,2,1,7};
    PrintArray(a,sizeof(a)/sizeof(int));
    QuickSort(a,0,sizeof(a)/sizeof(int)-1);
    PrintArray(a,sizeof(a)/sizeof(int));
}
int main()
{
    QuickSortTest();
    return 0;
}
