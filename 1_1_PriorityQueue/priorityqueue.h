#ifndef __PRI_QUEUE__
#define __PRI_QUEUE__

#include<iostream>
#include<assert.h>
#include<vector>
#include<functional>

namespace my_priorityqueue
{
    template<class T>
    struct less
    {
        bool operator()(const T& x,const T& y)
        {
            return x<y;
        }
    };

    template<class T>
    struct greater
    {
        bool operator()(const T& x, const T& y)
        {
            return x>y;
        }
    };


    template<class T,class Container=std::vector<T>,class Compare=less<typename Container::value_type>>
    class priority_queue
    {
    public:
        void AdjustUp(size_t child)
        {
            Compare com;
            size_t parent=(child-1)/2;
            while(child>0){
                if(com(_con[parent],_con[child])){
                    std::swap(_con[child],_con[parent]);
                    child=parent;
                    parent=(child-1)/2;
                }else{
                    break;
                }     
            }
        }

        void AdjustDown(size_t parent)
        {
            Compare com;
            size_t child =2*parent+1;
            while(child<_con.size()){
                if(child+1<_con.size() && com(_con[child],_con[child+1])){
                    child++;
                }
                if(com(_con[parent],_con[child])){
                    std::swap(_con[child],_con[parent]);
                    parent=child;
                    child=2*parent+1;
                }else{
                    break;
                }
            }
        }

        void push(const T& x)
        {
            _con.push_back(x);
            AdjustUp(_con.size()-1);
        }

        void pop()
        {
            std::swap(_con[0],_con[_con.size()-1]);
            _con.pop_back();
            AdjustDown(0);
        }

        T& top()
        {
            return _con[0];    
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

    void PriorityQueueTest()
    {
        //priority_queue<int,std::vector<int>,less<int>> pq;
        priority_queue<int,std::vector<int>,greater<int>> pq;

        pq.push(27);
        pq.push(15);
        pq.push(19);
        pq.push(18);
        pq.push(28);
        pq.push(34);
        pq.push(65);
        pq.push(49);
        pq.push(25);
        pq.push(37);
        while(!pq.empty()){
            std::cout<<pq.top()<<" ";
            pq.pop();
        }        
        std::cout<<std::endl;
    }
}


#endif
