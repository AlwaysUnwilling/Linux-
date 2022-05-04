#include<stdio.h>
#include<stdlib.h>


void swap(int* a, int* b)
{
  int tmp=*a;
  *a=*b;
  *b=tmp;
}
int getmidindex(int* arr,int left,int right)
{
  int mid=(left+right)>>1;
  if(arr[left]>arr[right]){
    if(arr[left]>arr[mid]){
      if(arr[right]>arr[mid]){
        return right;
      }else{
        return mid;
      }
    }else{
      return left;
    }
  }else{
    if(arr[left]>arr[mid]){
      return left;
    }else{
      if(arr[right]>arr[mid]){
        return mid;
      }else{
        return right;
      }
    }
  }
}
int partsort1(int* arr,int begin,int end)
{
  int midIndex=getmidindex(arr,begin,end);
  swap(&arr[midIndex],&arr[begin]);
  int keyi=begin;
  while(begin<end){
    while(begin<end && arr[end]>=arr[keyi]){
      end--;
    }
    while(begin<end && arr[begin]<=arr[keyi]){
      begin++;
    }
    swap(&arr[begin],&arr[end]);
  }
  swap(&arr[keyi],&arr[begin]);
  return begin;
}
int partsort2(int* arr,int begin,int end)
{
  int midIndex=getmidindex(arr,begin,end);
  swap(&arr[midIndex],&arr[begin]);
  int key=arr[begin];
  while(begin<end){
    while(begin<end && arr[end]>=key){
      end--;
    }
    arr[begin]=arr[end];
    while(begin<end && arr[begin]<=key){
      begin++;
    }
    arr[end]=arr[begin];
  }
  arr[begin]=key;
  return begin;
}
int partsort3(int* arr,int begin,int end)
{
  int midIndex=getmidindex(arr,begin,end);
  swap(&arr[midIndex],&arr[begin]);
  int keyi=begin;
  int prev=begin;
  int cur=begin;
  while(cur<=end){
    if(arr[cur]<arr[keyi]){
      ++prev;
      swap(&arr[prev],&arr[cur]);
    }else{
      ++cur;
    }
  }
  swap(&arr[keyi],&arr[prev]);
  return prev;
}
void quicksort(int* arr,int begin,int end)
{
  if(begin>=end){
    return ;
  }
  //int meetIndex=partsort1(arr,begin,end);
  //int meetIndex=partsort2(arr,begin,end);
  int meetIndex=partsort2(arr,begin,end);
  quicksort(arr,begin,meetIndex-1);
  quicksort(arr,meetIndex+1,end);
}
int main()
{
  int arr[]={4,3,7,1,9,8,4,3,5,14,0,8,11,23,-2,16};
  int n=sizeof(arr)/sizeof(int);
  quicksort(arr,0,n-1);
  for(int i=0;i<n;++i){
    printf("%d ",arr[i]);
  }
  printf("\n");
  return 0;
}

