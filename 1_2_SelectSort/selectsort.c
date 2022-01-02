#include"selectsort.h"



void PrintArray(int* a,int n)
{
    assert(a);
    printf("SelectSort: ");
    for(int i=0;i<n;++i){
        printf("%d ",a[i]);
    }
    printf("\n");
}
void swap(int* e1,int* e2)
{
    int tmp=*e1;
    *e1=*e2;
    *e2=tmp;
}
void SelectSort(int* a,int n)
{
    assert(a);
    int left=0,right=n-1;
    while(left<right){
        int maxIndex=left,minIndex=left;
        for(int i=left;i<=right;++i){
            if(a[i]<a[minIndex]){
                minIndex=i;
            }
            if(a[i]>a[maxIndex]){
                maxIndex=i;
            }
        }
        swap(&a[left],&a[minIndex]);
        if(left==maxIndex){
            maxIndex=minIndex; 
        }
        swap(&a[right],&a[maxIndex]);
        ++left;
        --right;
    }
}


void AdjustDown(int* a,int parent,int n)
{
    int child=parent*2+1;
    while(child<n){
        if(child+1<n && a[child+1]>a[child]){
            child++;
        }
        if(a[parent]<a[child]){
            swap(&a[parent],&a[child]);
            parent=child;
            child=parent*2+1;
        }else{
            break;
        }
    }
}
void HeapSort(int* a,int n)
{
    assert(a);
    for(int i=(n-2)/2;i>=0;--i){
        AdjustDown(a,i,n);
    }
    PrintArray(a,n);
    int end=n;
    while(end>0){
        swap(&a[0],&a[end-1]);
        --end;
        AdjustDown(a,0,end);
    }
}
