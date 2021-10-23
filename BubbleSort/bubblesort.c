#include"bubblesort.h"

void PrintArray(int* a,int n)
{
    for(int i=0;i<n;i++){
        printf("%d ",a[i]);
    }
    printf("\n");
}
void Swap(int* e1,int* e2)
{
    int tmp=*e1;
    *e1=*e2;
    *e2=tmp;
}
void BubbleSort(int* a,int n)
{
    assert(a);
    int end=n-1;
    while(end>0){
        int exchange=0;
        for(int i=0;i<end;i++){
            if(a[i]>a[i+1]){
                Swap(&a[i],&a[i+1]);
                exchange=1;
            }
        }
        if(exchange==0){
            break;
        }
        --end;
    }
}

