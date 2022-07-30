#ifndef B5323C53_429C_4EF3_AE4D_94504C40CEBF
#define B5323C53_429C_4EF3_AE4D_94504C40CEBF

#include<iostream>

class Task
{
private:
    int x;
    int y;
    char op;
public:
    Task(int _x,int _y,char _op)
    :x(_x),y(_y),op(_op)
    {}
    Task()
    {}
    void Run()
    {
        switch(op){
            case '+':
                std::cout<<x<<"+"<<y<<"="<<x+y<<std::endl;
            break;
            case '-':
                std::cout<<x<<"-"<<y<<"="<<x-y<<std::endl;
            break;
            case '*':
                std::cout<<x<<"*"<<y<<"="<<x*y<<std::endl;
            break;
            case '/':
                if(y!=0){
                    std::cout<<x<<"/"<<y<<"="<<x/y<<std::endl;
                }else{
                    std::cout<<"second data error!!! [y==0]"<<std::endl;
                }
            break;
            case '%':
                if(y!=0){
                    std::cout<<x<<"%"<<y<<"="<<x%y<<std::endl;
                }else{
                    std::cout<<"second data error!!! [y==0]"<<std::endl;
                }
            break;
            default:
                std::cout<<"Task error!"<<std::endl;
            break;
        }
    }
};

#endif /* B5323C53_429C_4EF3_AE4D_94504C40CEBF */
