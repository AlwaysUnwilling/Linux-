#include"heapsort.h"

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
void Adjustdown(int* a,int n,int root)
{
    int parent=root;
    int child=2*parent+1;
    int end=n;
    while(child<n){
        if(child+1<n && a[child+1]>a[child]){
            child++;
        }
        if(a[child]>a[parent]){
            Swap(&a[child],&a[parent]);
            parent=child;
            child=2*parent+1;
        }else{
            break;
        }
    }
}
void HeapSort(int* a,int n,int root)
{
    assert(a);
    for(int i=(n-2)/2;i>=0;--i){
        Adjustdown(a,n,i);
    }
    int end=n-1;
    while(end>0){
        Swap(&a[end],&a[0]);
        Adjustdown(a,end,0);
        --end;
    }
}
