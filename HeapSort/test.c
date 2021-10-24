#include"heapsort.h"


void HeapSortTest()
{
    int a[]={9,5,2,3,7,6,21,6,42,4,0,6,4,7,8,1};
    PrintArray(a,sizeof(a)/sizeof(int));
    HeapSort(a,sizeof(a)/sizeof(int),0);
    PrintArray(a,sizeof(a)/sizeof(int));
}
int main()
{
    HeapSortTest();
    return 0;
}
