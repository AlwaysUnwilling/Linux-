#include"insertsort.h"


void InsertSortTest()
{
    int a[]={8,12,3,5,14,56,2,0,1,7,10,9};
    PrintArray(a,sizeof(a)/sizeof(int));
    InsertSort(a,sizeof(a)/sizeof(int));
    PrintArray(a,sizeof(a)/sizeof(int));
}
void ShellSortTest()
{
    int a[]={8,12,3,5,14,56,2,0,1,7,10,9};
    PrintArray(a,sizeof(a)/sizeof(int));
    ShellSort(a,sizeof(a)/sizeof(int));
    PrintArray(a,sizeof(a)/sizeof(int));
}
int main()
{
    //InsertSortTest();
    ShellSortTest();
    return 0;
}
