#include<stdio.h>
#include<stdlib.h>
#include<assert.h>

//思想：对于要排序的数组，假设数组的[0,end]区间是有序的，那么把[end+1,n]的元素依次插入到
//有序区间内使整个数组有序。arr[end+1]与arr[end]比较，比arr[end]大则直接插入到arr[end]后
//面；如果比arr[end]小，则继续向arr[end]前面的数据进行比较，同时需要挪动数据。
void insertsort(int* arr,int n)
{
  assert(arr);
  int end=1;
  while(end<n){
    int index=end-1;
    int tmp=arr[end];
    while(index>=0){
      if(tmp>=arr[index]){
        break;
      }else{
        arr[index+1]=arr[index];
        index--;
      }
    } 
    arr[index+1]=tmp;
    end++;
  }
}
int main()
{
  int arr[]={5,2,4,6,1,3};
  int n=sizeof(arr)/sizeof(int);
  insertsort(arr,n);
  for(int i=0;i<n;++i){
    printf("%d ",arr[i]);
  }
  printf("\n");
  return 0;
}
