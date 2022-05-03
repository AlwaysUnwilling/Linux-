#include<stdio.h>
#include<stdlib.h>


void swap(int* a,int* b)
{
  int tmp=*a;
  *a=*b;
  *b=tmp;
}
void bubblesort(int* arr,int n)
{
  for(int i=0;i<n;++i){
    for(int j=1;j<n-i;++j){
      if(arr[j-1]>arr[j]){
        swap(&arr[j-1],&arr[j]);
      }
    }
  }
}
int main()
{
  int arr[]={4,3,7,1,9,8,4,3,5};
  int n=sizeof(arr)/sizeof(int);
  bubblesort(arr,n);
  for(int i=0;i<n;++i){
    printf("%d ",arr[i]);
  }
  printf("\n");
  return 0;
}

