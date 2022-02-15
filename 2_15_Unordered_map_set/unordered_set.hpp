#ifndef __UNORDERED_SET_HPP__
#define __UNORDERED_SET_HPP__

#include<iostream>
#include<vector>

namespace my_Hash
{
template<class K>
    class unordered_set
    {
        struct KoT
        {
            const K& operator()(const K& key)
            {
                return key;
            }
        };
    private:
        my_Hash::HashTable<K,K,KoT> _ht;
    public:
        typedef typename my_Hash::HashTable<K,K,KoT>::iterator iterator;
        iterator begin()
        {
            return _ht.begin();
        }
        iterator end()
        {
            return _ht.end();
        }
        std::pair<iterator,bool> insert(const K& key)
        {
            return _ht.insert(key);
        }
    };
}




#endif
