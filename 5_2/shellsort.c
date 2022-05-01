#include<stdio.h>
#include<stdlib.h>

//思想：插入排序最坏的情况（逆序）的事件复杂度是O(N^2),最好的情况下（有序或接近有序）是O(N)；
//因此如果一个需要排序的数组如果在进行插入排序前就接近有序那么可以大大降低插入排序的时间消耗---希尔排序
//1、预排序：使得数组中元素接近有序:先分组(间隔为gap(假设gap=3)分成一组)，对分组的数据进行插入排序
//2、直接插入排序

void shellsort(int* arr,int n)
{
  int gap=n;
  while(gap>1){
    gap=gap/3+1;
    for(int i=0;i<n-gap;++i){
      int end=i;
      int tmp=arr[end+gap];
      while(end>=0){
        if(arr[end]>=tmp){
          arr[end+gap]=arr[end];
        }else{
          break;
        }
        end-=gap;
      }
      arr[end+gap]=tmp;
    }
  }
}
int main()
{
  int arr[]={9,1,2,5,7,4,8,6,3,5};
  int n=sizeof(arr)/sizeof(int);
  shellsort(arr,n);
  for(int i=0;i<n;++i){
    printf("%d ",arr[i]);
  }
  printf("\n");
  return 0;
}
