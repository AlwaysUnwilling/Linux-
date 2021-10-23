#include"bubblesort.h"


void BubbleSortTest()
{
    int a[]={9,5,2,3,7,6,0,6,9,4,0,6,4,7,8,1};
    PrintArray(a,sizeof(a)/sizeof(int));
    BubbleSort(a,sizeof(a)/sizeof(int));
    PrintArray(a,sizeof(a)/sizeof(int));
}
int main()
{
    BubbleSortTest();
    return 0;
}
