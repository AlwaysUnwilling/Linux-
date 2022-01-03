#include"mergesort.h"


void PrintArray(int* a,int n)
{
    printf("MergeSort: ");
    for(int i=0;i<n;++i){
        printf("%d ",a[i]);
    }
    printf("\n");
}

void _Merge(int* a,int begin1,int end1,int begin2,int end2,int* tmp)
{
    int i=begin1;
    int j=begin1;
    while(begin1<=end1 && begin2<=end2){
        if(a[begin1]<=a[begin2]){
            tmp[i++]=a[begin1++];
        }else{
            tmp[i++]=a[begin2++];
        }
    }
    while(begin1<=end1){
        tmp[i++]=a[begin1++];
    }
    while(begin2<=end2){
        tmp[i++]=a[begin2++];
    }
    for(;j<=end2;++j){
        a[j]=tmp[j];
    }
}

void _MergeSort(int* a,int left,int right,int* tmp)
{
    int midIndex=(left+right)>>1;
    if(left>=right){
        return ;
    }
    _MergeSort(a,left,midIndex,tmp);
    _MergeSort(a,midIndex+1,right,tmp);
    //int begin1=left,end1=midIndex;
    //int begin2=midIndex+1,end2=right;
    //int i=left;
    //while(begin1<=end1 && begin2<=end2){
    //    if(a[begin1]<a[begin2]){
    //        tmp[i++]=a[begin1++];
    //    }else{
    //        tmp[i++]=a[begin2++];
    //    }
    //}

    //while(begin1<=end1){
    //    tmp[i++]=a[begin1++];
    //}

    //while(begin2<=end2){
    //    tmp[i++]=a[begin2++];
    //}

    //for(int j=left;j<=right;++j){
    //    a[j]=tmp[j];
    //}
    _Merge(a,left,midIndex,midIndex+1,right,tmp);
}
void MergeSort(int* a,int n)
{
    assert(a);
    int* tmp=(int*)malloc(sizeof(int)*n);
    if(tmp==NULL){
        perror("malloc fail!\n");
        exit(-1);
    }
    int left=0;
    int right=n-1;
    _MergeSort(a,left,right,tmp);
    free(tmp);
    tmp=NULL;
}


void MergeSortNonR(int* a,int n)
{
    assert(a);
    int* tmp=(int*)malloc(sizeof(int)*n);
    if(tmp==NULL){
        perror("malloc fail!\n");
        exit(-1);
    }
    int gap=1;
    while(gap<n){
        for(int i=0;i<n;i+=2*gap){
            int end=i+2*gap-1;
            if(i+gap>=n){
                break;
            }
            if(end>=n){
                end=n-1;
            }
            _Merge(a,i,i+gap-1,i+gap,end,tmp);
        }
        gap*=2;
    }
    free(tmp);
}
