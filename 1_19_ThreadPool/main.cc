#include"pthreadpool.hpp"


int main()
{
    my_PthreadPool::PthreadPool<int> tp;
    //server
    while(1){
        int x=rand()%10+1;
        my_PthreadPool::Task<int> t(x);
        tp.Push(t);
        sleep(1);
    }
    return 0;
}
