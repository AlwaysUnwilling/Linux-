#ifndef __BLOOMFILTER_HPP__
#define __BLOOMFILTER_HPP__

#include<iostream>
#include"bitset.hpp"

namespace my_BloomFilter
{
    struct HashStr1
	{
		size_t operator()(const std::string& str)
		{
			//BKDR
			size_t hash = 0;
			for (size_t i = 0; i < str.size(); ++i){
				hash *= 131;
				hash += str[i];
			}
			return hash;
		}
	};
	struct HashStr2
	{
		size_t operator()(const std::string& str)
		{
			//RSHash
			size_t hash = 0;
			size_t magic = 63689;//魔数
			for (size_t i = 0; i < str.size(); ++i){
				hash *= magic;
				hash += str[i];
				magic *= 378551;
			}
			return hash;
		}
	};
	struct HashStr3
	{
		size_t operator()(const std::string& str)
		{
			//SDBMHash
			size_t hash = 0;
			for (size_t i = 0; i < str.size(); ++i){
				hash *= 65599;
				hash += str[i];
			}
			return hash;
		}
	};
    template<size_t N,
    class K=std::string,
    class Hash1=HashStr1,
    class Hash2=HashStr2,
    class Hash3=HashStr3>
    class BloomFilter
    {
    private:
        my_BitSet::BitSet<N> _bs;
    public:
        void Set(const K& key)
        {
            size_t index1=Hash1()(key)%N;
            size_t index2=Hash2()(key)%N;
            size_t index3=Hash3()(key)%N;
            _bs.set(index1);
            _bs.set(index2);
            _bs.set(index3);
        }
        bool Test(const K& key)
        {
            size_t index1=Hash1()(key)%N;
            if(!_bs.test(index1)){
                return false;
            }
            size_t index2=Hash2()(key)%N;
            if(!_bs.test(index2)){
                return false;
            }
            size_t index3=Hash3()(key)%N;
            if(!_bs.test(index3)){
                return false;
            }
            return true;
        }
    };
    void test_bloomfilter()
	{
		BloomFilter<100> bf;
		bf.Set("abcd");
		bf.Set("aadd");
		bf.Set("bcad");

		std::cout << bf.Test("abcd") << std::endl;
		std::cout << bf.Test("aadd") << std::endl;
		std::cout << bf.Test("bcad") << std::endl;
	}
}





#endif
