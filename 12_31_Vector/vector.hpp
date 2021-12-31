#ifndef __VECTOR__
#define __VECTOR__

#include<iostream>
#include<string.h>
#include<algorithm>
#include<string>
#include<assert.h>

namespace my_vector
{
    template<class T>
    class vector
    {
    public:
        typedef T* iterator;   
        typedef const T* const_iterator;
        vector()
        :_start(nullptr)
        ,_finish(nullptr)
        ,_endofstorage(nullptr)
        {}
        vector(const vector<T>& v)
        :_start(nullptr)
        ,_finish(nullptr)
        ,_endofstorage(nullptr)
        {
            if(this!=&v){
                _start=new T[v.capacity()];
                //memcpy(_start,v._start,sizeof(T)*v.size());//如果是深拷贝的自定义类型，使用memcpy就会出问题
                for(size_t i=0;i<v.size();++i){
                    _start[i]=v._start[i];
                }
                _finish=_start+v.size();
                _endofstorage=_start+v.capacity();
            }
        }
        //vector<T>& operator=(const vector<T>& v)
        //{
        //    if(this!=&v){

        //        vector<T> tmp(v);
        //        delete[] _start;
        //        _start=tmp._start;
        //        _finish=tmp._finish;
        //        _endofstorage=tmp._endofstorage;
        //    }
        //    return *this;
        //}
        template<class Iterator>
        vector(Iterator first,Iterator last)
        :_start(nullptr)
        ,_finish(nullptr)
        ,_endofstorage(nullptr)
        {
            while(first!=last){
                push_back(*first);
                ++first;
            }
        }
        vector<T>& operator=(vector<T> v)
        {
            swap(_start,v._start);
            swap(_finish,v._finish);
            swap(_endofstorage,v.endofstprage);
            return *this;
        }
        size_t size()const
        {
            return _finish-_start;
        }
        size_t capacity()const
        {
            return _endofstorage-_start;
        }
        void reserve(size_t n)
        {
            if(n>capacity()){
                T* tmp=new T[n];
                size_t sz=size();
                //memcpy(tmp,_start,sizeof(T)*sz); 
                for(size_t i=0;i<size();++i){
                    tmp[i]=_start[i];
                }
                delete[] _start;
                _start=tmp;
                _endofstorage=_start+n;
                _finish=_start+sz;
            }
        }
        void resize(size_t n,const T& val=T())
        {
            if(n>capacity()){
                T* tmp=new T[n];
                size_t sz=size();
                memcpy(tmp,_start,sizeof(T)*sz);
                for(size_t i=0;i<n-sz;i++){
                    (tmp+sz)[i]=val;
                }
                delete[] _start;
                _start=tmp;
                _finish=_start+n;
                _endofstorage=_start+n;
            }else if(n>size() && n<=capacity()){
                for(size_t i=0;i<n-size();++i){
                    (_start+size())[i]=val;
                }
                _finish=_start+n;
                _endofstorage=_start+n;
            }else{
                _finish=_start+n;
                _endofstorage=_start+n;
            }
        }
        iterator begin()
        {
            return _start;
        }
        const_iterator begin()const
        {
            return _start;
        }
        iterator end()
        {
            return _finish;
        }
        const_iterator end()const
        {
            return _finish;
        }
        T& operator[](size_t i)
        {
            assert(i<size());
            return _start[i];
        }
    
        void push_back(const T& val)
        {
            if(_finish==_endofstorage){
                size_t newcapacity=capacity()==0?4:capacity()*2;
                reserve(newcapacity);
            }
            *_finish=val;
            _finish++;
        }
        void pop_back()
        {
            assert(size());
            _finish--;
        }
        void insert(iterator pos,const T& val)
        {
            assert(pos);
            size_t n=pos-_start;
            if(_finish==_endofstorage){
                size_t len=pos-_start;
                size_t newcapacity=capacity()==0?4:capacity()*2;
                reserve(newcapacity);
                pos=_start+len;
            }           
            auto end=_finish-1;
            while(end>=pos){
                *(end+1)=*end;
                --end;
            }
            *pos=val;//一旦发生增容，导致pos迭代器失效
            ++_finish;
        }
        iterator erase(iterator pos)
        {
            assert(pos);
            auto end=pos;
            while(end<_finish-1){
                *end=*(end+1);
                end++;
            }
            --_finish;
            return pos;
        }
        ~vector()
        {
            if(_start){
                delete[] _start;
                _start=_finish=_endofstorage=nullptr;
            }
        }
    private:
        iterator _start;
        iterator _finish;
        iterator _endofstorage;
    };

    void VectorPushBackTest()
    {
        vector<int> v;
        v.push_back(1);
        v.push_back(2);
        v.push_back(3);
        v.push_back(4);
        v.push_back(5);

        for(auto e:v){
            std::cout<<e<<" ";
        }
        std::cout<<std::endl;
        for(size_t i=0;i<v.size();++i){
            std::cout<<v[i]<<" ";
        }
        std::cout<<std::endl;
        vector<int>::iterator it=v.begin();
        while(it!=v.end()){
            std::cout<<*it<<" ";
            ++it;
        }
        std::cout<<std::endl;
        v.resize(10,6);
        for(auto e:v){
            std::cout<<e<<" ";
        }
        std::cout<<std::endl;
        v.resize(6,7);
        for(auto e:v){
            std::cout<<e<<" ";
        }
        std::cout<<std::endl;
        v.resize(3,0);
        for(auto e:v){
            std::cout<<e<<" ";
        }
        std::cout<<std::endl;
        vector<int>::iterator pos=std::find(v.begin(),v.end(),1);
        v.insert(pos,0);
        for(auto e:v){
            std::cout<<e<<" ";
        }
        std::cout<<std::endl;
        v.push_back(4);
        v.push_back(6);
        v.push_back(8);
        v.push_back(7);
        vector<int>::iterator p=v.begin();
        while(p!=v.end()){
            if(*p%2==0){
                p=v.erase(p);
            }else{
                ++p;
            }
        }
        for(auto e:v){
            std::cout<<e<<" ";
        }
        std::cout<<std::endl;
        vector<int>::const_iterator conit=v.begin();
        while(conit!=v.end()){
            std::cout<<*conit<<" ";
            //*conit=8;
            ++conit;
        }
        std::cout<<std::endl;

        vector<int> v1(v);
        for(auto e:v){
            std::cout<<e<<" ";
        }
        std::cout<<std::endl;
        vector<int> v2=v1;

        for(auto e:v){
            std::cout<<e<<" ";
        }
        std::cout<<std::endl;

        vector<std::string> vs;
        vs.push_back("111111111111111111111111111111111111111111111");
        vs.push_back("222222222222222222222222222222222222222222222");
        vs.push_back("333333");
        vs.push_back("44444444444");
        vs.push_back("22222222222222222222233333333333333333333333333");
        vs.push_back("5555");
        vs.push_back("66666666666666666666666666");
        for(auto e:vs){
            std::cout<<e<<" ";
        }
        std::cout<<std::endl;
    }
}


#endif
