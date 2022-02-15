#ifndef __UNORDERED_MAP_HPP__
#define __UNORDERED_MAP_HPP__

#include"HashTable.hpp"

namespace my_Hash
{
template<class K,class V>
    class unordered_map
    {
        struct KoT
        {
            const K& operator()(const std::pair<K,V>& kv)
            {
                return kv.first;
            }
        };
    private:
        my_Hash::HashTable<K,std::pair<K,V>,KoT> _ht;
    public:
        typedef typename my_Hash::HashTable<K,std::pair<K,V>,KoT>::iterator iterator;
        iterator begin()
        {
            return _ht.begin();
        }
        iterator end()
        {
            return _ht.end();
        }
        
        std::pair<iterator,bool> insert(const std::pair<K,V>& kv)
        {
            return _ht.insert(kv);
        }
        V& operator[](const K& key)
        {
            auto it=_ht.insert(std::make_pair(key,V()));
            return it.first->second;
        }
    };
}




#endif 
