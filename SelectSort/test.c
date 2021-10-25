#include"selectsort.h"


void SelectSortTest()
{
    int a[]={9,5,2,3,7,6,21,6,42,4,0,6,4,7,8,1};
    PrintArray(a,sizeof(a)/sizeof(int));
    SelectSort(a,sizeof(a)/sizeof(int));
    PrintArray(a,sizeof(a)/sizeof(int));
}
int main()
{
    SelectSortTest();
    return 0;
}
