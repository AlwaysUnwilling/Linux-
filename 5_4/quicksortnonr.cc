#include<iostream>
#include<stack>
#include<stdlib.h>

using namespace std;
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
  int cur=begin+1;
  while(cur<=end){
    if(arr[cur]<arr[keyi]){
      ++prev;
      swap(&arr[prev],&arr[cur]);
    }
    ++cur;
  }
  swap(&arr[keyi],&arr[prev]);
  return prev;
}
void quicksortnonr(int* arr,int begin,int end)
{
  stack<pair<int,int>> st;
  if(end-begin>0){
    st.push({begin,end});
  }
  while(!st.empty()){
    int left=st.top().first;
    int right=st.top().second;
    st.pop();
    int meetIndex=partsort3(arr,left,right);
    if(meetIndex-left>1){
      st.push({left,meetIndex-1});
    }
    if(right-meetIndex>1){
      st.push({meetIndex+1,right});
    }
  }
}
int main()
{
  int arr[]={4,3,7,1,9,8,4,3,5,14,0,8,11,23,-2,16};
  int n=sizeof(arr)/sizeof(int);
  quicksortnonr(arr,0,n-1);
  for(int i=0;i<n;++i){
    printf("%d ",arr[i]);
  }
  printf("\n");
  return 0;
}

