#ifndef __AUTO_PTR_HPP__
#define __AUTO_PTR_HPP__

#include<iostream>

namespace my_SmartPtr
{
template<class T>
    class auto_ptr
    {
    private:
        T* _ptr;
    public:
        auto_ptr(const auto_ptr<T>& t)
        :_ptr(t._ptr)
        {
            t._ptr=nullptr;
        }
        auto_ptr<T>& operator=(const auto_ptr<T>& t)
        {
            if(this!=&t){
                delete _ptr;
                _ptr=t._ptr;
                t._ptr=nullptr;
            }
            return *this;
        }
        auto_ptr(T* t):_ptr(t)
        {}
        T& operator*()
        {
            return *_ptr;
        }
        T* operator->()
        {
            return _ptr;
        }
        ~auto_ptr()
        {
            if(_ptr){
                delete ptr;
            }
        }
    };

}


#endif
