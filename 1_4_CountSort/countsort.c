#include"countsort.h"



void PrintAarray(int* a,int n)
{
    printf("CountSort: ");
    for(int i=0;i<n;++i){
        printf("%d ",a[i]);
    }
    printf("\n");
}

void CountSort(int* a,int n)
{
    assert(a);
    int max=0,min=0;
    for(int i=0;i<n;++i){
        if(a[i]>max){
            max=a[i]; 
        }
        if(a[i]<min){
            min=a[i];
        }
    }
    int range=max-min+1;
    int* count=(int*)malloc(sizeof(int)*range);
    if(count==NULL){
        perror("malloc fail!\n");
        exit(-1);
    }
    for(int i=0;i<n;++i){
        count[a[i]]++;
    }
    int j=0;
    for(int i=0;i<range;++i){
        while(count[i]--){
            a[j++]=i+min;
        }   
    }
    free(count);
}
