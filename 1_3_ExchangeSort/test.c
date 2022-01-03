#include"exchangesort.h"



void BubbleSortTest()
{
    int a[]={10,1,5,3,7,8,12,8,0,18,11,4,9,21,-1};
    PrintArray(a,sizeof(a)/sizeof(int));
    BubbleSort(a,sizeof(a)/sizeof(int));
    PrintArray(a,sizeof(a)/sizeof(int));
}

void QuickSortTest()
{
    int a[]={10,1,5,3,7,8,12,8,0,18,11,4,9,21,-1};
    PrintArray(a,sizeof(a)/sizeof(int));
    QuickSort(a,0,sizeof(a)/sizeof(int)-1);
    PrintArray(a,sizeof(a)/sizeof(int));
}
void QuickSortNorTest()
{
    int a[]={10,1,5,3,7,8,12,8,0,18,11,4,9,21,-1};
    PrintArray(a,sizeof(a)/sizeof(int));
    QuickSort(a,0,sizeof(a)/sizeof(int)-1);
    PrintArray(a,sizeof(a)/sizeof(int));
}
int main()
{
    //BubbleSortTest();
    //QuickSortTest();
    QuickSortNorTest();
    return 0;
}
