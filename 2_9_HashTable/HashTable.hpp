#ifndef __HASHTABLE_HPP__
#define __HASHTABLE_HPP__

#include<iostream>
#include<string>
#include<vector>

namespace my_Hash
{
    enum State
    {
        EXIST,
        DELETE,
        EMPTY
    };
    template<class K,class V>
    struct HashData
    {
        std::pair<K,V> _data;
        State _state=EMPTY;
    };
    template<class K>
    struct HashValue
    {
        int operator()(const K& key)
        {
            return key;
        }
    };
    template<>
    struct HashValue<std::string>
    {
        int operator()(const std::string& s)
        {
            int value=0;
            for(auto ch:s){
                value+=ch;
                value*=131;
            }
            return value;
        }
    };
    template<class K,class V,class HashValue>
    class HashTable
    {
       // struct Kot
       // {
       //     K& operator()(const T& t)
       //     {
       //         return t.first;
       //     }
       // };
    private:
        std::vector<HashData<K,V>> _table;
        size_t _n=0;    //有效数据
    public:
        bool insert(const std::pair<K,V>& t)
        {
            HashData<K,V>* ret=find(t.first);
            if(ret){
                return false;
            }
            if(_table.size()==0){
                _table.resize(10);
            } 
            if(_n*10/_table.size()>7){
                HashTable<K,V,HashValue> newht;
                newht._table.resize(_table.size()*2);
                for(auto& e:_table){
                    newht.insert(e._data);
                }
                _table.swap(newht._table);
            }
            HashValue hV;
            size_t i=1;
            size_t index=hV(t.first)%_table.size();
            while(_table[index]._state==EXIST){
                index+=i;
                index%=_table.size();
                ++i;
            }
            _table[index]._data=t;
            _table[index]._state=EXIST;
            ++_n;
            return true;
        }
        bool erase(const K& key)
        {
            HashData<K,V>* ret=find(key);
            if(ret){
                ret->_state=DELETE;
                --_n;
                return true;
            }
            return false;
        }
        HashData<K,V>* find(const K& key)
        {
            
            if(_table.size()==0){
                return nullptr;
            }
            HashValue hV;
            for(auto& e:_table){
                if(e._state==EXIST && hV(e._data.first)==hV(key)){
                    return &e;
                }
            }
            return nullptr;
        }
    };
    void TestHashTable()
    {
        HashTable<int,int,HashValue<int>> ht;
        ht.insert(std::make_pair(1,1));
        ht.insert(std::make_pair(2,2));
        ht.insert(std::make_pair(3,3));
        ht.insert(std::make_pair(4,4));
        ht.insert(std::make_pair(5,5));
        ht.insert(std::make_pair(6,6));
        ht.erase(2);
        if(ht.find(3)){
            std::cout<<"找到了！"<<std::endl;
        }else{
            std::cout<<"没有找到！"<<std::endl;
        }
        std::cout<<std::endl;
        HashTable<std::string,int,HashValue<std::string>> ht1;
        std::string s[]={"apple","apple","banana","apple","banana","pear"};
        for(auto& e:s){
            if(auto it=ht1.find(e)){
                it->_data.second++;
            }else{
                ht1.insert(std::make_pair(e,1));
            }
        }
        
    }
}



#endif
