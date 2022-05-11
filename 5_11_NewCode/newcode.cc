#include<iostream>
#include<cstdio>
#include<vector>

using namespace std;

//美国节日
/*
和中国的节日不同，美国的节假日通常是选择某个月的第几个星期几这种形式，因此每一年的放假日期都不相同。具体规则如下：
* 1月1日：元旦
* 1月的第三个星期一：马丁·路德·金纪念日
* 2月的第三个星期一：总统节
* 5月的最后一个星期一：阵亡将士纪念日
* 7月4日：美国国庆
* 9月的第一个星期一：劳动节
* 11月的第四个星期四：感恩节
* 12月25日：圣诞节
现在给出一个年份，请你帮忙生成当年节日的日期。
 * */

bool IsLeapYear(int year)
{
    return year%400==0 || (year%4==0 && year%100!=0);
}
int MonthDays[]={0,31,28,31,30,31,30,31,31,30,31,30,31};
//求year-month-day这一天是该年中的第几天
int nDays(int y,int m,int d)
{
    int n=d;
    for(int i=1;i<m;++i){
        n+=MonthDays[i];
    }
    if(m>2 && IsLeapYear(y)){
        n++;
    }
    return n;
}
//求year-month-day从基准值0-12-31日是星期天(7)到
//改天的天数对7取余（MOD 7 的同余数）
int diff(int y,int m,int d)
{
    return (y-1) + (y-1)/4 - (y-1)/100 + (y-1)/400 + nDays(y,m,d);
}
//计算year-month-day是周几
int week(int y,int m,int d)
{
    int w=diff(y,m,d)%7;
    if(w==0){
        w=7;
    }
    return w;
}
//已知当月1日是星期w，求第n个星期e是几号
int m1(int w,int n,int e)
{
    return 1+(n-1)*7+(7-w+e)%7;
}
//已知下月的第一天是星期w，求该月的最后一个星期e是几号
int m2(int w)
{
    int d=(w==1?7:(w-1));
    return 32-d;
}
int main()
{
    int y;
    while(cin>>y){
        int w;
        printf("%d-01-01\n",y);
        
        w=week(y,1,1);
        printf("%d-01-%02d\n",y,m1(w,3,1));
        
        w=week(y,2,1);
        printf("%d-02-%02d\n",y,m1(w,3,1));
        
        w=week(y,6,1);
        printf("%d-05-%02d\n",y,m2(w));

        printf("%d-07-04\n",y);
        
        w=week(y,9,1);
        printf("%d-09-%02d\n",y,m1(w,1,1));
        
        w=week(y,11,1);
        printf("%d-11-%02d\n",y,m1(w,4,4));
        
        printf("%d-12-25\n\n",y);
    }
    return 0;
}

//分解因数
/*
所谓因子分解，就是把给定的正整数a，分解成若干个素数的乘积，即 a = a1 × a2 × a3 × ... × an,并且 1 < a1 ≤ a2 ≤ a3 ≤ ... ≤ an。其中a1、a2、...、an均为素数。 先给出一个整数a，请输出分解后的因子。
 * */

void GetFactors(vector<int>& v,int n)
{
    for(int i=2;i*i<=n;++i){
        while(n%i==0){
            v.push_back(i);
            n/=i;
        }
    }
    if(n!=1){
        v.push_back(n);
    }
}
int main()
{
    int n;
    vector<int> v;
    while(cin>>n){
        v.clear();
        GetFactors(v,n);
        cout<<n<<" = ";
        for(int i=0;i<v.size();++i){
            cout<<v[i];
            if(i<v.size()-1){
                cout<<" * ";
            }
        }
        cout<<endl;
    }
    return 0;
}
