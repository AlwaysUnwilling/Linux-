/*************************************************************************
	> File Name: test.cpp
	> Author: 
	> Mail: 
	> Created Time: Fri 17 Dec 2021 08:47:42 PM CST
 ************************************************************************/
 //求1+2+3+...+n;要求：不能使用乘除法，for，while，if else，switch，case等关键字及判断语句(A?B:C)

#include<iostream>
using namespace std;


class Add
{
    //friend class Solution;//也可以定义友缘类来访问该类的私有成员
public:
    Add()
    {
        _ret+=_i;
        _i++;
    }
    static int GetRet()
    {
        return _ret;
    }
    static void Init()
    {
        _i=1;
        _ret=0;
    }
private:
    static int _i;
    static int _ret;
};

int Add::_i=1;
int Add::_ret=0;

class Solution
{
public:
    int sum_Solution(int n){
        Add::Init();
        Add *arr=new Add[n];
        return Add::GetRet();
    }   
};


int main()
{
    cout<<Solution().sum_Solution(5)<<endl;
    return 0;
}
