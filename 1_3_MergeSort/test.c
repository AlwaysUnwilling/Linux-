#include"mergesort.h"




void MergeSortTest()
{
    int a[]={18,2,5,7,12,6,2,3,7,9,10,11,4,14,21,0,0};
    PrintArray(a,sizeof(a)/sizeof(int));
    MergeSort(a,sizeof(a)/sizeof(int));
    PrintArray(a,sizeof(a)/sizeof(int));
}
void MergeSortNonRTest()
{
    int a[]={18,2,5,7,12,6,2,3,7,9,10,11,4,14,21,0,0};
    PrintArray(a,sizeof(a)/sizeof(int));
    MergeSortNonR(a,sizeof(a)/sizeof(int));
    PrintArray(a,sizeof(a)/sizeof(int));
}
int main()
{
    MergeSortTest();
    MergeSortNonRTest();
    return 0;
}
