#ifndef __UNIQUE_PTR_HPP__
#define __UNIQUE_PTR_HPP__

#include<iostream>

namespace my_SmartPtr
{
template<class T>
    class unique_ptr
    {
    private:
        T* _ptr;
    public:
        unique_ptr(const unique_ptr<T>& t)=delete;
        unique_ptr<T>& operator=(const unique_ptr<T>& t)=delete;
        unique_ptr(T* t):_ptr(t)
        {}
        T& operator*()
        {
            return *_ptr;
        }
        T* operator->()
        {
            return _ptr;
        }
        ~unique_ptr()
        {
            if(_ptr){
                delete ptr;
            }
        }
    };

}


#endif
