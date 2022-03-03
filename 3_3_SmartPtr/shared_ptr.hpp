#ifndef __SHARED_PTR_HPP__
#define __SHARED_PTR_HPP__

#include<iostream>
#include<mutex>

namespace my_SmartPtr
{
template<class T>
    class shared_ptr
    {
    private:
        T* _ptr;
        int* _count;
        mutex* _pmtx;
    private:
        void AddRefCount()
        {
            _pmtx->lock();
            ++(*_count);
            _pmtx->unlock();
        }
        void DelRefCount()
        {
            _pmtx->lock();
            bool flag=false;
            if(--(*_count)==0){
                delete ptr;
                delete _count;
                flag=true;
            }
            _pmtx->unlock();
            if(flag==true){
                delete _pmtx;
            }
        }
    public:
        shared_ptr(const shared_ptr<T>& t)
        :_ptr(t._ptr),_count(t._count),_pmtx(t._pmtx)
        {
            AddRefCount();
        }
        shared_ptr<T>& operator=(const shared_ptr<T>& t)
        {
            if(_ptr!=t._ptr){
                DelRefCount();
                _ptr=t._ptr;
                _count=t._count;
                _pmtx=t._pmtx;
                AddRefCount();
            }
            return *this;
        }
        shared_ptr(T* t):_ptr(t),_count(new int(1)),_pmtx(new mutex)
        {}
        T& operator*()
        {
            return *_ptr;
        }
        T* operator->()
        {
            return _ptr;
        }
        T* get()const
        {
            return _ptr;
        }
        ~shared_ptr()
        {
            DelRefCount();
        }
    };

    template<class T>
    class weak_ptr
    {
    private:
        T* _ptr;
    public:
        weak_ptr()=default;
        weak_ptr(const shared_ptr<T>& sp)
        :_ptr(sp.get())
        {}
        weak_ptr<T> operator=(const shared_ptr<T>& sp)
        {
            _ptr=sp.get();
            return *this;
        }
        T& operator*()
        {
            return *_ptr;
        }
        T* operator->()
        {
            return _ptr;
        }
    };

}


#endif
