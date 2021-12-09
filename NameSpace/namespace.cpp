#include<iostream>
#include<stdio.h>
#include<string.h>
//命名冲突
//using namespace std;
//C++库为了防止命名冲突，把自己库里面的东西都定义在了一个std的命名空间中
//要使用标准库中的东西，有三种方式：
//1、指定命名空间--std::cout--缺点：麻烦，每个用到std库里面的东西都需要指定std库，但也是最规范的方式
//2、把std整个展开--using namespace std;缺点：把std库展开相当于库里面的东西都到全局域了，容易造成命名冲突
//3、对部分常用的库里面的东西展开--using namesp cout;针对前俩种折中的解决办法，项目中也经常使用
//以上三种方法对于自己定义的命名空间一样可以使用；
int a=100;
namespace myspace
{
    int scanf=10;
    int strlen=20;
    //命名空间中可以嵌套另一个命名空间
    namespace myspace_1
    {
        int c;
        int d;
        int Sub(int left,int right)
        {
            return left-right;
        }
    }
}

int main()
{
    //C语言解决不了冲突的问题
    //C++命名空间，名字隔离
    printf("%x\n",scanf);//默认访问的是局部或者全局的（就近原则）
    printf("%x\n",strlen);

    //指定访问myspace命名空间中的 
    printf("%x\n",myspace::scanf);
    printf("%x\n",myspace::strlen);

    myspace::myspace_1::c=10;
    myspace::myspace_1::d=20;
    int ret= myspace::myspace_1::Sub(myspace::myspace_1::c,myspace::myspace_1::d);
    printf("ret=%d\n",ret);

    int a=1;
    printf("a=%d\n",a);//就近原则，局部优先
    printf("a=%d\n",::a);//域作用限定符::前面空白表示全局
    return 0;
}
