#ifndef __MAP_HPP__
#define __MAP_HPP__
#include"RBTree.hpp"

namespace my_Map
{
    template<class K,class V>
    class map
    {
        struct Compare
        {
            const K& operator()(const std::pair<K,V>& kv)
            {
                return kv.first;
            }
        };
    private:
        my_RBTree::RBTree<K,std::pair<const K,V>,Compare> _rbt;
    public:
        typedef typename my_RBTree::RBTree<K,std::pair<const K,V>,Compare>::iterator iterator;
        typedef typename my_RBTree::RBTree<K,std::pair<const K,V>,Compare>::const_iterator const_iterator;
        typedef typename my_RBTree::RBTree<K,std::pair<const K,V>,Compare>::reverse_iterator reverse_iterator;
        reverse_iterator rbegin()
        {
            return _rbt.rbegin();
        }
        reverse_iterator rend()
        {
            return _rbt.rend();
        }
        iterator begin()
        {
            return _rbt.begin();
        }
        const_iterator begin()const
        {
            return _rbt.begin();
        }
        iterator end()
        {
            return _rbt.end();
        }
        const_iterator end()const
        {
            return _rbt.end();
        }
        std::pair<iterator,bool> insert(const std::pair<K,V>& kv)
        {
           return  _rbt.Insert(kv);
        }
        V& operator[](const K& key)
		{
            std::pair<iterator,bool> ret= _rbt.Insert(std::make_pair(key,V()));
			return ret.first->second;
		}
    };
}

#endif
