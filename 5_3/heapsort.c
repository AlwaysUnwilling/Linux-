#include<stdio.h>
#include<stdlib.h>


void swap(int* a,int* b)
{
  int tmp=*a;
  *a=*b;
  *b=tmp;
}
void AdjustDown(int* arr,int parent,int n)
{
  int child=2*parent+1;
  while(child<n){
    if(child+1<n && arr[child]<arr[child+1]){
      child++;
    }
    if(arr[parent]<arr[child]){
      swap(&arr[child],&arr[parent]);
      parent=child;
      child=2*parent+1;
    }else{
      break;
    }
  }
}
void heapsort(int* arr,int n)
{
  for(int i=(n-2)/2;i>=0;--i){
    AdjustDown(arr,i,n);
  }
  for(int i=n-1;i>0;--i){
    swap(&arr[0],&arr[i]);
    AdjustDown(arr,0,i);
  }
}
int main()
{
  int arr[]={4,3,7,1,9,8,4,3,5};
  int n=sizeof(arr)/sizeof(int);
  heapsort(arr,n);
  for(int i=0;i<n;++i){
    printf("%d ",arr[i]);
  }
  printf("\n");
  return 0;
}

