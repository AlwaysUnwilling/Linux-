#ifndef __REVERSEITERATOR_HPP__
#define __REVERSEITERATOR_HPP__

#include<iostream>

template<class Iterator>
struct ReverseIterator
{
    typedef typename Iterator::reference Ref;
    typedef typename Iterator::pointer Ptr;
    typedef ReverseIterator<Iterator> Self;
    Iterator _it;
    ReverseIterator(Iterator it)
    :_it(it)
    {}
    Ref operator*()
    {
        return *_it;
    }
    Ptr operator->()
    {
        return _it.operator->();
    }
    Self& operator++()
    {
        --_it;
        return *this;
    }
    bool operator!=(const Self& s)
    {
        return _it!=s._it;
    }
    bool operator==(const Self& s)
    {
        return !(_it.operator!=(s));
    }
};







#endif
