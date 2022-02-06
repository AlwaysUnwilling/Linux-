#ifndef __SET_HPP__
#define __SET_HPP__

#include"RBTree.hpp"

namespace my_Set
{
    template<class K>
    class set
    {
        struct Compare
        {
            const K& operator()(const K& key)
            {
                return key;
            }
        };
    private:
        my_RBTree::RBTree<K,K,Compare> _rbt;
    public:
        typedef typename my_RBTree::RBTree<K,K,Compare>::iterator iterator;
        iterator begin()
        {
            return _rbt.begin();
        }
        iterator end()
        {
            return _rbt.end();
        }
        bool insert(const K& key)
        {
           return  _rbt.Insert(key).second;
        }  
    };   
}
#endif
