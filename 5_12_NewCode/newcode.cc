#include<iostream>
#include<cstdio>

using namespace std;

//标题：斐波那契凤尾
/*
 *NowCoder号称自己已经记住了1-100000之间所有的斐波那契数。
为了考验他，我们随便出一个数n，让他说出第n个斐波那契数。当然，斐波那契数会很大。因此，如果第n个斐波那契数不到6位，则说出该数；否则只说出最后6
位。
 */
 
int main()
{
  int border=-1;
  long long ans[100000]={0};
  ans[0]=1;
  ans[1]=2;
  for(int i=2;i<100000;++i){
    long long next=ans[i-1]+ans[i-2];
    if(border==-1 && next>=100000){
      border=i+1;
    }
    ans[i]=next%100000;
  }
  int n;
  while(cin>>n){
    long long ret=ans[n-1];
    if(n>border){
      printf("%06d\n",ret);
    }else{
      printf("%d\n",ret);
    }
  }
  return 0;
}


//标题：淘宝网店
/*
 *【淘宝网店】NowCoder在淘宝上开了一家网店。他发现在月份为素数的时候，当月每天能赚1元；否则每天能赚2元。
现在给你一段时间区间，请你帮他计算总收益有多少。
 * */

#include <cstdio>
#include <cmath>
#include <iostream>

//闰年判断函数
inline int leap_year(int year)
{
	return year % 400 == 0 || (year % 4 == 0 && year % 100 != 0);
}

//足年天数
inline int profit_of_year(int year)
{
	return 2 * 31
         + 1 * 28
         + 1 * 31
         + 2 * 30
         + 1 * 31
         + 2 * 30
         + 1 * 31
         + 2 * 31
         + 2 * 30
         + 2 * 31
         + 1 * 30
         + 2 * 31
		 + leap_year(year);
}

//判断这个月份是不是质数月
inline bool prime(int n)
{
	return n == 2 || n == 3 || n == 5 || n == 7 || n == 11; 
}

//求出一个日子是这一年的第几天
int profit_of_this_year(int year, int month, int day)
{
	if(!prime(month))
	{
		day *= 2;
	}
	
	while(--month)
	{
		switch(month)
		{
			case 1:
			case 8:
			case 10:
			case 12:
				day += 62;
				break;
			case 3:
			case 5:
			case 7:
				day += 31;
				break;
			case 4:
			case 6:
			case 9:
				day += 60;
				break;
			case 11:
				day += 30;
				break;
			case 2:
				day += 28 + leap_year(year);
				break;
			default:;
		}
	}
	return day;
}

int main()
{
    int year1, month1, day1, year2, month2, day2;
    int count_profit = 0;
    
    while (std::cin >> year1 >> month1 >> day1 >> year2 >> month2 >> day2)
    {
    	count_profit = 0;
    	
    	count_profit += profit_of_year(year1) -
        				profit_of_this_year(year1, month1, day1 - 1); 
        //这里的day1 - 1虽然有可能会出现0日，但是实际2月0日就相当于1月31日，所以不影响结果。
    	count_profit += profit_of_this_year(year2, month2, day2);
    	if(year1 == year2) //避免起点和终点是同一年，如果是同一年，要减掉这一年的天数。
    	{
    		count_profit -= profit_of_year(year1); 
		}
    	
    	for(int i = year1 + 1; i < year2; i++) //中间足年每一年的天数
    	{
    		count_profit += profit_of_year(i);
		}
		
		std::cout << count_profit << std::endl;
	}
    
    return 0;
}
