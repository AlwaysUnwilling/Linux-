#include<stdio.h>
#include<stdlib.h>
#include<assert.h>

//直接选择排序：每次遍历选出最大最小的值，最大值放在数组末尾，最小值放在数组首尾；然后继续在
//剩下的元素中继续上次的操作。

void swap(int* a,int* b)
{
  int tmp=*a;
  *a=*b;
  *b=tmp;
}
void selectsort(int* arr,int n)
{
  assert(arr);
  int left=0;
  int right=n-1;
  while(left<right){
    int minIndex=left;
    int maxIndex=right;
    for(int i=left;i<=right;++i){
      if(arr[i]<arr[minIndex]){
        minIndex=i;
      }
      if(arr[i]>arr[maxIndex]){
        maxIndex=i;
      }
    }
    swap(&arr[left],&arr[minIndex]);
    if(left==maxIndex){
      maxIndex=minIndex;
    }
    swap(&arr[right],&arr[maxIndex]);
    ++left;
    --right;
  }
}
int main()
{
  int arr[]={10,9,8,7,6,5,4,3,2,1,0};
  int n=sizeof(arr)/sizeof(int);
  selectsort(arr,n);
  for(int i=0;i<n;++i){
    printf("%d ",arr[i]);
  }
  printf("\n");
  return 0;
}
