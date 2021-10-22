#include"shellsort.h"


void ShellSortTest()
{
    int a[]={9,5,2,3,7,6,21,6,42,4,0,6,4,7,8,1};
    PrintArray(a,sizeof(a)/sizeof(int));
    ShellSort(a,sizeof(a)/sizeof(int));
    PrintArray(a,sizeof(a)/sizeof(int));

}
int main()
{
    ShellSortTest();
    return 0;
}
