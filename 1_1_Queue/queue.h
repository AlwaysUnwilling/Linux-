#ifndef __QUEUE__
#define __QUEUE__

#include<iostream>
#include<deque>
#include<list>
#include<assert.h>

namespace my_queue
{
    template<class T,class Container=std::deque<T>>
    class queue
    {
    public:
        void push(const T& x)
        {
            _con.push_back(x);
        }
        void pop()
        {
            _con.pop_front();
        }
        T& front()
        {
            return _con.front();
        } 
        T& back()
        {
            return _con.back();
        }
        size_t size()
        {
            return _con.size();
        }
        bool empty()
        {
            return _con.empty();
        }

    private:
        Container _con;
    };

    void QueueTest()
    {
        //queue<int> q;
        queue<int,std::list<int>> q;
        q.push(1);
        q.push(2);
        q.push(3);
        q.push(4);
        q.push(5);
        q.push(6);
        while(!q.empty()){
            std::cout<<q.front()<<" ";
            q.pop();
        }
        std::cout<<std::endl;
    }
}


#endif
