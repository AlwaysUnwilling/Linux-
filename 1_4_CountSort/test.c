#include"countsort.h"





void CountSortTest()
{
    //int a[]={9,2,5,7,4,8,10,0,3,7,2,3,3,5,6,9};
    int a[]={19,20,19,17,17,10,15,11,12,11,13,12,18,14,13,18,10};
    PrintAarray(a,sizeof(a)/sizeof(int));
    CountSort(a,sizeof(a)/sizeof(int)) ;  
    PrintAarray(a,sizeof(a)/sizeof(int));
}
int main()
{
    CountSortTest();
    return 0;
}
