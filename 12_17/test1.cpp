/*************************************************************************
	> File Name: test1.cpp
	> Author: 
	> Mail: 
	> Created Time: Fri 17 Dec 2021 09:44:48 PM CST
 ************************************************************************/

#include<iostream>
using namespace std;
//描述
//根据输入的日期，计算是这一年的第几天。
//保证年份为4位数且日期合法。
//进阶：时间复杂度：，空间复杂度：
//输入描述：
//输入一行，每行空格分割，分别是年，月，日

//输出描述：
//输出是这一年的第几天
//

int GetMonthDay(int year,int month)
{
    int MonthDay[13]={0,31,28,31,30,31,30,31,31,30,31,30,31};
    if(month==2 && (year%400==0 || (year%4==0 && year%100!=0))){
        MonthDay[2]=29;
    }
    return MonthDay[month];
}
int main()
{
    int year=0,month=1,day=1;
    cin>>year>>month>>day;
    int firstday=1,firstmonth=1,firstyear=year;
   int num=0;
    while(firstmonth!=month){
        firstday++;
        num++;
        if(firstday>GetMonthDay(year, firstmonth)){
            firstday=1;
            firstmonth++;
        }
    }
    num+=day;
    cout <<num<<endl;
    return 0;
}

