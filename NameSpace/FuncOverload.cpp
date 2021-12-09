/*************************************************************************
	> File Name: FuncOverload.cpp
	> Author: 
	> Mail: 
	> Created Time: Thu 09 Dec 2021 09:37:12 PM CST
 ************************************************************************/

#include<iostream>
using namespace std;


//缺省参数:使调用更加灵活；
//注意：缺省参数不能在函数声明和定义中同时出现，最好是在函数声明是给定缺省值
void TestFunc(int a=0)
{
    cout <<a<<endl;
}
void TestFunc1(int a=0,int b=0,int c=1)//全缺省
{
    cout <<a<<" "<<b<<" "<<c<<endl;
}
void TestFunc2(int a,int b=0,int c=1)//半缺省：必须从右往左连续缺省
{
    cout <<a<<" "<<b<<" "<<c<<endl;
}

int main()
{
    TestFunc();
    TestFunc(10);
    TestFunc1();
    TestFunc1(10,20,30);

    TestFunc2(5);
    TestFunc2(5,6,7);
    return 0;
}
