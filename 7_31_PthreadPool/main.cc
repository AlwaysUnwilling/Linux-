#include"pthreadpool.hpp"
#include<memory>
#include<ctime>
#include<cstdlib>
#include<string>
#include<unistd.h>

void TestPthreadPool()
{
    srand((unsigned long)time(nullptr));
    std::string Op("+-*/%");
    my_PthreadPool::PthreadPool<my_PthreadPool::Task<int,int>,int,int>* pq=new my_PthreadPool::PthreadPool<my_PthreadPool::Task<int,int>,int,int>;
    pq->PthreadPoolInit();
    std::shared_ptr<my_PthreadPool::PthreadPool<my_PthreadPool::Task<int,int>,int,int>> sp(pq);
    while(true){
        int x=rand()%100;
        int y=rand()%100;
        char op=Op[rand()%Op.size()];
        my_PthreadPool::Task<int,int> t(x,y,op);
        sp->Push(t);
        sleep(1);
    }
}
int main()
{
    TestPthreadPool();
    return 0;
}