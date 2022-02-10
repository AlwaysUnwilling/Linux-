#ifndef __HASHTABLE_HPP__
#define __HASHTABLE_HPP__

#include<iostream>
#include<vector>
#include<string>


namespace my_Hash
{
    template<class K,class V>
    struct HashData
    {
        struct HashData<K,V>* _next;
        std::pair<K,V> _kv;
        HashData(const std::pair<K,V>& kv)
        :_next(nullptr),_kv(kv)
        {}
    };
    template<class K>
    struct Hash
    {
        int operator()(const K& key)
        {
            return key;
        }
    };
    template<>
    struct Hash<std::string>
    {
        int operator()(const std::string& s)
        {
            int HashValue=0;
            for(auto ch:s){
                HashValue+=ch;
                HashValue*=131;
            }
            return HashValue;
        }
    };
    template<class K,class V,class HashKey=Hash<K>>
    class HashTable
    {
        typedef struct HashData<K,V> _Node;
    private:
        std::vector<_Node*> _table;
        size_t _n=0;
    public:
        bool insert(const std::pair<K,V>& kv)
        {
            if(find(kv.first)){
                return false;
            }
            if(_table.size()==0){
                _table.resize(10,nullptr);
            }
            Hash<K> hk;
            if(_n*10/_table.size()>7){
                HashTable<K,V> newht;
                newht._table.resize(_table.size()*2,nullptr);
                for(auto& e:_table){
                    if(e){
                        size_t index=hk(e->_kv.first)%newht._table.size();
                        e->_next=newht._table[index];
                        newht._table[index]=e;
                        e=nullptr;
                        ++newht._n;
                    }
                }
                _table.swap(newht._table);
            }
            size_t index=hk(kv.first)%_table.size();
            _Node* newnode=new _Node(kv);
            newnode->_next=_table[index];
            _table[index]=newnode;
            ++_n;
            return true;
        }
        bool erase(const K& key)
        {
            _Node* ret=find(key);
            Hash<K> hk;
            if(ret){
                size_t index=hk(key)%_table.size();
                if(ret==_table[index]){
                    _table[index]=ret->_next;
                }else{
                    _Node* cur=_table[index];
                    while(cur){
                        if(cur->_next==ret){
                            cur->_next=ret->_next;
                            break;
                        }
                        cur=cur->_next;
                    }
                }
                delete ret;
                --_n;
                return true;
            }else{
                return false;
            }
        }
        _Node* find(const K& key)
        {
            if(_table.size()==0){
                return nullptr;
            }
            Hash<K> hk;
            size_t index=hk(key)%_table.size();
            _Node* cur=_table[index];
            while(cur){
                if(cur->_kv.first==key){
                    return cur;
                }
                cur=cur->_next;
            }
            return nullptr;
        }
    };
    void TestHashTable()
    {
        HashTable<int,int> ht;
        ht.insert(std::make_pair(4,4));
        ht.insert(std::make_pair(14,14));
        ht.insert(std::make_pair(24,24));
        ht.insert(std::make_pair(5,5));
        ht.insert(std::make_pair(15,15));
        ht.insert(std::make_pair(25,25));
        ht.insert(std::make_pair(6,6));
        ht.insert(std::make_pair(16,16));
        ht.insert(std::make_pair(26,26));
        ht.insert(std::make_pair(36,36));
        ht.insert(std::make_pair(33,33));
    }
    void TestHashTable1()
    {
        HashTable<std::string,int> ht;
        ht.insert(std::make_pair("sort",1));
        ht.insert(std::make_pair("string",2));
        ht.insert(std::make_pair("left",3));
        ht.insert(std::make_pair("sort",3));
    }
}






#endif
