/*************************************************************************
	> File Name: C++_IO.cpp
	> Author: 
	> Mail: 
	> Created Time: Thu 09 Dec 2021 09:14:45 PM CST
 ************************************************************************/

#include<iostream>
using namespace std;
//c++std::couthe std::cin对比C语言printf scanf有社么区别？
//自动识别类型（原理：函数重载+运算符重载）(注意：cin遇到空格”、“TAB”、“回车都会结束；scanf()以空格、回车、制表符作为字符串的终止符，不读走空格、制表符、回车符，仍留在缓冲区中)
int main()
{
    int a=10;
    int* p=&a;
    printf("%d,%p\n",a,p);
    cout<<a<<","<<p<<endl;

    char str[10];
    std::cin>>a;
    std::cin>>str;
    cout<<a<<";"<<str<<endl;
    return 0;
}
