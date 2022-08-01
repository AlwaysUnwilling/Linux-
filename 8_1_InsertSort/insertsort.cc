#include<iostream>
#include<vector>

using namespace std;

void TestShellSort(vector<int>& v)
{
  int n=v.size();
  int gap=n;
  while(gap > 1){
    gap=gap/3+1;
    for(int i=0;i < n-gap;++i){
      int tmp=v[i+gap];
      int j=i;
      while(j >= 0){
        if(v[j] < tmp){
          break;
        }
        v[j+gap]=v[j];
        j-=gap;
      }
      v[j+gap]=tmp;
    }
  }
  for(const auto& e:v){
    std::cout<<e<<" ";
  }
  std::cout<<std::endl;
}
void TestInsertSort(vector<int>& v)
{
  int n=v.size();
  for(int i=1;i < n;++i){
    int tmp=v[i];
    int j=i-1;
    while(j >= 0){
      if(v[j] < tmp){
        break;
      }
      v[j+1]=v[j];
      --j;
    }
    v[j+1]=tmp;
  }
  for(const auto& e:v){
    std::cout<<e<<" ";
  }
  std::cout<<std::endl;
}
int main()
{
  vector<int> v{10,9,8,7,6,5,4,3,2,1,0};
  TestInsertSort(v);
  vector<int> v1{10,9,8,7,6,5,4,3,2,1,0};
  TestShellSort(v1);
  return 0;
}
