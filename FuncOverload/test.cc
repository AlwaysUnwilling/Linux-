#include<iostream>

using namespace std;

//C语言不允许定义同名函数
//C++可以---函数重载:函数的参数类型(类型 or 个数 or 顺序不同)不同或者个数不同构成函数重载,对返回值没有要求
//注意：函数的缺省参数不能构成函数重载；
//  
//c++是如何支持函数重载的？为什么c语言不支持？
//回答：在链接时c语言遇到相同的函数名不会生成相应的.o文件（因为c语言中函数名在机器码中保存的就是函数名本身）；
//  而c++中，函数名在机器码中会修饰它的函数名（不仅仅保留函数名，还会保留函数的参数类型等相关信息），从而可以区分开相同的函数名。<函数名修饰规则>

int Add(int x,int y)
{
    return x+y;
}
double Add(double x,double y)
{
    return x+y;
}
char Add(char x,char y)
{
    return x+y;
}
int Add(int x,int y,int z)
{
    return x+y+z;
}
//int Add(int x,int y,int z=10)//该函数与函数int Add(int x,int y)构成重载，但是
//在Add(1,2)调用时会造成调用不明确，导致编译不过
//{
  //  return x+y+z;
//}
int main()
{
    char a='1';
    char b='2';
    cout<<Add(1,2)<<endl;
    cout<<Add(1.1,1.2)<<endl;
    cout<<Add(a,b)<<endl;
    cout<<Add(1,2,3)<<endl;
    return 0;
}
