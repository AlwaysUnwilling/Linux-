#include<iostream>
#include<string>
#include<map>

//第一种打印可变模板参数方法：递归
void ShowListArg()
{
    std::cout<<std::endl;
    return ;
}
template<class T,class ...Args>
void ShowListArg(T value,Args... args)
{                             
    std::cout<<value<<" ";
    ShowListArg(args...);
}
template<class ...Args>
void ShowList(Args... args)
{
    std::cout<<sizeof...(args)<<std::endl;
    ShowListArg(args...);
}

//第二种打印可变模板参数方法：逗号表达式（逗号表达式：从左往右依次执行，结果是最后一个逗号表达式的结果）
template<class T>
void PrintArg(T t)
{
    std::cout<<t<<" ";
}
template<class ...Args>
void ShowList1(Args... args)
{
    /*if(sizeof...(args)==0){ //这里递归结束不能通过sizeof...(args)==0来结束：因为里的判断是执行时
        return;             //逻辑；而数组的大小是在运行前（编译时就已经确定了大小）；编译时的条件判断
    } */                      //只会看条件编译;
    //列表初始化
    int arr[]={(PrintArg(args),0)...};//(PrintArg(args),0)先执行PrintArg(args),再执行0，结果是0；即相当于
                                    //arr中存放的都是整型0；即：展开后：(PrintArg(args),0),(PrintArg(args1),0)...Args
                                    //从而推得可变参数包的个数即数组的大小。
    std::cout<<std::endl;
}


int main()
{
    ShowList();
    ShowList(1,2,"sss");
    ShowList1();
    ShowList1(1,2,"sss");
    return 0;
}
