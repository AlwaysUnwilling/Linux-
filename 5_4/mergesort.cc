#include<iostream>
#include<vector>

using namespace std;

void merge(vector<int>& v,vector<int>& tmp,int left,int mid,int right)
{
  int begin1=left,end1=mid;
  int begin2=mid+1,end2=right;
  int tmpi=0;
  while(begin1<=end1 && begin2<=end2){
    if(v[begin1]<v[begin2]){
      tmp[tmpi++]=v[begin1++]; 
    }else{
      tmp[tmpi++]=v[begin2++];
    }
  }
  while(begin1<=end1){
    tmp[tmpi++]=v[begin1++];
  }
  while(begin2<=end2){
    tmp[tmpi++]=v[begin2++];
  }
  tmpi=0;
  int vi=left;
  while(vi<=end2){
    v[vi++]=tmp[tmpi++];
  }
}
void mergersort(vector<int>& v,vector<int>& tmp,int left,int right)
{
  if(left>=right){
    return ;
  }
  int mid=(left+right)>>1;
  mergersort(v,tmp,left,mid);
  mergersort(v,tmp,mid+1,right);
  merge(v,tmp,left,mid,right);
}
void mergersortnonr(vector<int>& v,vector<int>& tmp,int left,int right)
{
  int n=right-left+1;
  int gap=1;
  while(gap<n){
    for(int i=0;i<n;i+=2*gap){
      int begin=i;
      int mid=i+gap-1;
      int end=i+2*gap-1;
      if(end>=n){
        end=n-1;
      }
      if(mid+1>=n){
        break;
      }
      merge(v,tmp,begin,mid,end);
    }
    gap*=2;
  }
}
int main()
{
  vector<int> v{10,6,7,1,3,9,4,2,5,8,0};
  vector<int> tmp;
  tmp.resize(v.size());
  mergersort(v,tmp,0,v.size()-1);
  for(const auto& e:v){
    cout<<e<<" ";
  }
  cout<<endl;
  return 0;
}
