/*************************************************************************
	> File Name: test2.cpp
	> Author: 
	> Mail: 
	> Created Time: Fri 17 Dec 2021 10:00:11 PM CST
 ************************************************************************/

#include<iostream>
using namespace std;
//给出年分m和一年中的第n天，算出第n天是几月几号。
//输入描述：
//输入包括两个整数y(1<=y<=3000)，n(1<=n<=366)。
//输出描述：
//可能有多组测试数据，对于每组数据， 按 yyyy-mm-dd的格式将输入中对应的日期打印出来。
int GetMonthDay(int year,int month){
    int MonthDay[13]={0,31,28,31,30,31,30,31,31,30,31,30,31};
    if(month==2 && (year%400==0 || (year%4==0 && year%100!=0))){
        MonthDay[2]=29;
    }
    return MonthDay[month];
}
int main()
{
    int year=0,n=0;
    cin>>year>>n;
    int month=1,day=1,num=1;
    while(num!=n){
        num++;
        day++;
        if(day>GetMonthDay(year, month)){
            month++;
            day=1;
        }
    }
    printf("%04d-%02d-%02d\n",year,month,day);
   
    
    return 0;
}
