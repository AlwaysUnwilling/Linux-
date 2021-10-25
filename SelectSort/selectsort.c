#include"selectsort.h"

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
void SelectSort(int* a,int n)
{
    assert(a);
    int begin=0;
    int end=n-1;
    while(begin<end){
        int mini,maxi;
        mini=maxi=begin;
        for(int i=begin+1;i<=end;i++){
            if(a[i]>a[maxi]){
                maxi=i; 
            }
            if(a[i]<a[mini]){
                mini=i;
            }
        }
        Swap(&a[begin],&a[mini]);
        if(begin==maxi){
            maxi=mini;
        }
        Swap(&a[end],&a[maxi]);
        ++begin;
        --end;
    }
}
