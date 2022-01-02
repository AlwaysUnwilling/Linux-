#include"selectsort.h"




void SelectSortTest()
{
    int a[]={2,7,3,7,8,12,5,16,10,22,3,0,6,9};
    PrintArray(a,sizeof(a)/sizeof(int));
    SelectSort(a,sizeof(a)/sizeof(int));
    PrintArray(a,sizeof(a)/sizeof(int));
}

void HeapSortTest()
{
    int a[]={2,7,3,7,8,12,5,16,10,22,3,0,6,9};
    PrintArray(a,sizeof(a)/sizeof(int));
    HeapSort(a,sizeof(a)/sizeof(int));
    PrintArray(a,sizeof(a)/sizeof(int));
}
int main()
{
    //SelectSortTest();
    HeapSortTest();
    return 0;
}
