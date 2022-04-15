#include<iostream>
#include<algorithm>
#include<vector>

using namespace std;

//标题：计算日期到天数转换
/*
 【计算日期到天数转换】
根据输入的日期，计算是这一年的第几天。
保证年份为4位数且日期合法。
 */

int GetDayOfYear(int year,int month,int day)
{
  static int monthDays[13]={0,31,28,31,30,31,30,31,31,30,31,30,31};
  int ret=0;
  if((year%4==0 && year%100!=0) || year%400==0)
  {
    monthDays[2]=29;
  }
  for(size_t i=1;i<month;++i){
    ret+=monthDays[i];
  }
  ret+=day;
  return ret;
}
int main()
{
  int year=0,month=0,day=0;
  std::cin>>year>>month>>day;
  std::cout<<GetDayOfYear(year,month,day)<<std::endl;
  return 0;
}

//标题：幸运的袋子
/*
 【幸运的袋子】一个袋子里面有n个球，每个球上面都有一个号码(拥有相同号码的球是无区别的)。如果一个袋子是幸运的当且仅当所有球的号码的和大于所有球的
号码的积。
例如：如果袋子里面的球的号码是{1, 1, 2, 3}，这个袋子就是幸运的，因为1 + 1 + 2 + 3 > 1 * 1 * 2 * 3
你可以适当从袋子里移除一些球(可以移除0个,但是别移除完)，要使移除后的袋子是幸运的。现在让你编程计算一下你可以获得的多少种不同的幸运的袋子。
 */

int _GetNumOfLuckyBags(std::vector<int>& bag,int pos,int bagSum,int bagMul)
{
  int ret=0;
  int end=pos;
  while(end<bag.size()){
    bagMul*=bag[end];
    bagSum+=bag[end];
    if(bagSum>bagMul){
      ret+=_GetNumOfLuckyBags(bag,end+1,bagSum,bagMul)+1;
    }else if(bag[end]==1){
      ret+=_GetNumOfLuckyBags(bag,end+1,bagSum, bagMul);
    }else{
      break;
    }
    bagSum-=bag[end];
    bagMul/=bag[end];
    while(end<bag.size()-1 && bag[end]==bag[end+1]){
      end++;
    }
    end++;
  }
  return ret;
}
int GetNumOfLuckyBags(std::vector<int>& bag)
{
  if(bag.size()==1){
    return 0;
  }
  int bagMul=1;
  int bagSum=0;
  return _GetNumOfLuckyBags(bag,0,bagSum,bagMul);
}
int main()
{
  int n=0;
  std::cin>>n;
  std::vector<int> bag;
  bag.resize(n);
  int x=0;
  for(size_t i=0;i<n;++i){
    std::cin>>x;
    bag[i]=x;
  }
  sort(bag.begin(),bag.end());
  std::cout<<GetNumOfLuckyBags(bag)<<std::endl;
  return 0;
}
