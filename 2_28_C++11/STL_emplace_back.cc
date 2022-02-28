#include<iostream>
#include<list>


//在STL容器中增加了emplace_back();可变参数的插入；这里的“&&”是万能引用---既可以是引用左值也可以引用右值
//emplace_back(Args... args) 除了可以像push_back()/insert()...等一样的插入格式外还可以插入一组数据包，
//使用数据包进行构造对象插入到容器中（使用定位new--- ::new(static_cast<void*>(p))T(forward<Args>(args)...)）
template<class ...Args>
void emplace_back(Args&&... args) 
{
    
}


int main()
{
    std::list<std::pair<int ,char>> lt;
    std::make_pair<int,char>(10,'a');
    lt.emplace_back(10,'a');  //独有--数据包直接构造   效率更高！---直接构造
    lt.emplace_back(std::make_pair(10,'a'));  //右值对象 构造+移动构造
    lt.emplace_back(std::make_pair<int,char>(10,'a'));
    //lt.emplace_back({10,'a'});   //不支持

    lt.push_back(std::make_pair(10,'a')); 
    lt.push_back(std::pair<int,char>(10,'a'));
    lt.push_back({10,'a'});  // c++11中的链表初始化--自定义类型链表初始化

    for(auto e:lt){
        std::cout<<e.first<<":"<<e.second<<std::endl;
    }
    return 0;
}
