#ifndef __LIST__
#define __LIST__

#include<iostream>
#include<assert.h>
#include<algorithm>
#include<utility>

namespace my_list
{
    template<class T>
    struct _list_node_
    {
        T _val;
        _list_node_<T>* _next;
        _list_node_<T>* _prev;
        _list_node_<T>(const T& val=T())
        :_val(val)
        ,_next(nullptr)
        ,_prev(nullptr)
        {}
    };

    template<class T,class Ref,class Ptr>
    struct _list_iterator_
    {
        typedef _list_node_<T> _node;
        typedef _list_iterator_<T,Ref,Ptr> Self;
        _node* _pnode;
        _list_iterator_<T,Ref,Ptr>(_node* pnode)
        :_pnode(pnode)
        {}

        Ref operator*()
        {
            return _pnode->_val;
        }

        Ptr operator->()
        {  
            return &(_pnode->_val);
        }

        bool operator!=(const Self& s)
        {
            return _pnode!=s._pnode;
        }

        bool operator==(const Self& s)const
        {
            return _pnode==s._pnode;
        }

        Self& operator++()
        {
            _pnode=_pnode->_next;
            return *this;  
        }

        Self operator++(int)
        {
            Self tmp(*this);
            _pnode=_pnode->_next;
            return tmp;
        }

        Self& operator--()
        {
            _pnode=_pnode->_prev;
            return *this;
        }

        Self operator--(int)
        {
            Self tmp(*this);
            _pnode=_pnode->_prev;
            return tmp;
        }
    };

    template<class T>
    class list
    {
        typedef _list_node_<T> _node;
    public:
        typedef _list_iterator_<T,T&,T*> iterator;
        typedef _list_iterator_<T,const T&,const T*> const_iterator;    
        list()
        {
            _head=new _node;
            _head->_next=_head;
            _head->_prev=_head;
        }
        
        list(const list<T>& ls)
        {
            //_head=new _node;
            //_node* tail=_head;
            //_node* cur=(ls._head)->_next;
            //while(cur!=ls._head){
            //    _node* tmp=new _node(cur->_val);
            //    tail->_next=tmp;
            //    tmp->_prev=tail;
            //    tail=tail->_next;
            //    cur=cur->_next;
            //}
            //tail->_next=_head;
            //_head->_prev=tail;
            _head=new _node;
            _head->_next=_head;
            _head->_prev=_head;
            for(const auto& e:ls){
                push_back(e);
            }
        }
           
        list<T>& operator=( list<T> ls)
        {
            std::swap(_head,ls._head);
            return *this;
        }

        //list<T>& operator=(const list<T>& ls)
        //{
        //    if(this!=&ls){
        //        clear();
        //        for(const auto& e:ls){
        //            push_back(e);
        //        }
        //    }
        //    return *this;
        //}

        void clear()
        {
            //_node* cur=_head->_next;
            //_node* next=nullptr;
            //while(cur!=_head){
            //    next=cur->_next;
            //    delete cur;
            //    cur=next;
            //}
            iterator it=begin();
            while(it!=end()){
                it=erase(it);
            }
        }

        ~list()
        {
            clear();
            delete _head;
            _head=nullptr;
        }

        iterator begin()
        {
            return iterator(_head->_next);     
        }

        const_iterator begin()const
        {
            return const_iterator(_head->_next);     
        }

        iterator end()
        {
            return iterator(_head);
        }

        const_iterator end()const
        {
            return const_iterator(_head);
        }

        void insert(iterator pos,const T& val)
        {
            assert(pos._pnode);
            _node* newNode=new _node(val);
            _node* cur=pos._pnode;
            _node* prev=cur->_prev;
            prev->_next=newNode;
            newNode->_prev=prev;
            newNode->_next=cur;
            cur->_prev=newNode;
        }

        iterator erase(iterator pos)
        {
            assert(pos._pnode && pos._pnode!=_head);
            _node* cur=pos._pnode;
            _node* prev=cur->_prev;
            _node* next=cur->_next;
            prev->_next=next;
            next->_prev=prev;
            delete pos._pnode;
            return iterator(next);
        }

        void push_back(const T& val)
        {
            //_node* newNode=new _node(val);
            //_node* tail=_head->_prev;
            //_head->_prev=newNode;
            //newNode->_next=_head;
            //tail->_next=newNode;
            //newNode->_prev=tail;
            insert(end(),val);
        }

        void pop_back()
        {
            erase(--end());
        }

        void push_front(const T& val)
        {
            insert(begin(),val);
        }

        void pop_front()
        {
            erase(begin());
        }

    private:
        _node* _head;
    };
      

    void ListPrint(const list<int>& lt)
    {
        list<int>::const_iterator it=lt.begin();
        while(it!=lt.end()){
            std::cout<<*it<<" ";
            ++it;
        }
        std::cout<<std::endl;
    }

    void ListTest()
    {
        list<int> ls;
        ls.push_back(1);
        ls.push_back(2);
        ls.push_back(3);
        ls.push_back(4);
        ls.push_back(5);
        ls.push_back(6);
        list<int>::iterator it=ls.begin();
        while(it!=ls.end()){
            std::cout<<*it<<" ";
            ++it;
        }
        std::cout<<std::endl;
        ls.push_back(7);
        ls.push_back(8);
        ls.push_back(9);
        ls.push_back(10);
        ListPrint(ls);

        ls.insert(ls.begin(),11);
        ls.push_front(12);
        ls.push_front(13);
        ListPrint(ls);
        ls.pop_front();
        ListPrint(ls);
        ls.pop_back();
        ListPrint(ls);
        list<int> ls1(ls);
        ListPrint(ls1);
        list<int> ls2;
        ls2=ls;
        ListPrint(ls2);
    }




}



#endif
