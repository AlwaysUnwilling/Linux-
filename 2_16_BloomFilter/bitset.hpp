#ifndef __BITSET_HPP__
#define __BITSET_HPP__

#include<iostream>
#include<vector>


namespace my_BitSet
{
    template<size_t N>
    class BitSet
    {
    private:
        std::vector<int> _bits;
        size_t _num;
    public:
        BitSet()
        {
            _bits.resize(N/32+1,0);
            _num=0;
        }
        void set(size_t x)
        {
            int i=x/32;
            int j=x%32;
            _bits[i]|=(1<<j);
            ++_num;
        }
        void reset(size_t x)
        {
            int i=x/32;
            int j=x%32;
            _bits[i]&=(~(1<<j));
            --_num;
        }
        bool test(size_t x)
        {
            int i=x/32;
            int j=x%32;
            return _bits[i]&(1<<j);
        }
    };
}




#endif
