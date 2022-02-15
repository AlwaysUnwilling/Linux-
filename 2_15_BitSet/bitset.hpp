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
    void test_bitset()
	{
		BitSet<101> b;
		b.set(100);
		b.set(98);
		b.set(10);
		b.set(97);
		b.set(5);
		b.reset(98);
		for (size_t i = 0; i < 101; i++)
		{
			printf("[%d]:%d\n", i, b.test(i));
		}
    }   
}




#endif
