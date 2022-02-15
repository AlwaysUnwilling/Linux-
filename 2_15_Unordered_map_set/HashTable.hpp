#ifndef __HASHTABLE_HPP__
#define __HASHTABLE_HPP__

#include<iostream>
#include<vector>
#include<string>


namespace my_Hash
{
    template<class T>
    struct HashData
    {
        struct HashData<T>* _next;
        T _data;
        HashData(const T& data)
        :_next(nullptr),_data(data)
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

    template<class K,class T,class KoT,class HashKey>
    class HashTable;

    template<class K,class T,class KoT,class HashKey=Hash<K>>
    struct __HTIterator
    {
        typedef __HTIterator<K,T,KoT,HashKey> Self;
        typedef HashData<T> _Node;
        typedef HashTable<K,T,KoT,HashKey> _HT;
        _HT* _pht;
        _Node* node;
        __HTIterator(_Node* _node,_HT* pht)
        :node(_node),_pht(pht)
        {}
        T& operator*()
        {
            return node->_data;
        }
        T* operator->()
        {
            return &node->_data;
        }
        Self& operator++()
        {
            if(node->_next){
                node=node->_next;
            }else{
                KoT kt;
                HashKey hk;
                size_t index=hk(kt(node->_data))%_pht->_table.size();
                index++;
                while(index<_pht->_table.size()){
                    if(_pht->_table[index]){
                        node=_pht->_table[index];
                        return *this;
                    }
                    ++index;
                }
                node=nullptr;
            }
            return *this;
        }
        bool operator!=(const Self& s)
        {
            return node!=s.node;
        }
        bool operator==(const Self& s)
        {
            return !node.operator!=(s);
        }
    };
    template<class K,class T,class KoT,class HashKey=Hash<K>>
    class HashTable
    {
        typedef struct HashData<T> _Node;
        friend struct __HTIterator<K,T,KoT,HashKey>;
    private:
        std::vector<_Node*> _table;
        size_t _n=0;
    public:
        typedef struct __HTIterator<K,T,KoT,HashKey> iterator;
        iterator begin()
        {
            size_t i=0;
            while(i<_table.size()){
                if(_table[i]){
                    return iterator(_table[i],this);
                }
                ++i;
            }
            return end();
        }
        iterator end()
        {
            return iterator(nullptr,this);
        }
        HashTable()=default;
        HashTable(const HashTable& ht)
        {
            _table.resize(ht._table.size());
            _n=ht._n;
            for(size_t i=0;i<ht._table.size();++i){
                auto cur=ht._table[i];
                if(cur){
                    while(cur){
                        _Node* copy=new _Node(cur->_data);
                        copy->_next=_table[i];
                        _table[i]=copy;
                        cur=cur->_next;
                    }
                }else{
                    _table[i]=nullptr;
                }    
            }
        }
        HashTable& operator=(HashTable ht)
        {
            if(this!=&ht){
                _table.swap(ht._table);
                std::swap(_n,ht._n);
            }
            return *this;
        }
        ~HashTable()
        {
            for(auto& vc:_table){
                _Node* cur=vc;
                while(cur){
                    _Node* next=cur->_next;
                    delete cur;
                    cur=next;
                }
                vc=nullptr;
            }
            _n=0;
        }    
    
        std::pair<iterator,bool> insert(const T& data)
        {
            KoT kt;
            auto ret=find(kt(data));
            if(ret!=end()){
                return std::make_pair(ret,false);
            }
            if(_table.size()==0){
                _table.resize(10,nullptr);
            }
            HashKey hk;
            if(_n*10/_table.size()>7){
                HashTable<K,T,KoT> newht;
                newht._table.resize(_table.size()*2,nullptr);
                for(auto& e:_table){
                    if(e){
                        size_t index=hk(kt(e->_data))%newht._table.size();
                        e->_next=newht._table[index];
                        newht._table[index]=e;
                        e=nullptr;
                        ++newht._n;
                    }
                }
                _table.swap(newht._table);
            }
            size_t index=hk(kt(data))%_table.size();
            _Node* newnode=new _Node(data);
            newnode->_next=_table[index];
            _table[index]=newnode;
            ++_n;
            return std::make_pair(iterator(newnode,this),true);
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
        iterator find(const K& key)
        {
            if(_table.size()==0){
                return iterator(nullptr,this);
            }
            Hash<K> hk;
            KoT kt;
            size_t index=hk(key)%_table.size();
            _Node* cur=_table[index];
            while(cur){
                if(kt(cur->_data)==key){
                    return iterator(cur,this);
                }
                cur=cur->_next;
            }
            return iterator(nullptr,this);
        }
    };
}






#endif
