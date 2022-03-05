/*************************************************************************
	> File Name: leetcode.c
	> Author: 
	> Mail: 
	> Created Time: Sun 06 Mar 2022 12:25:26 AM CST
    > About:LRU 缓存:请你设计并实现一个满足  LRU (最近最少使用) 缓存 约束的数据结构。
实现 LRUCache 类：
LRUCache(int capacity) 以 正整数 作为容量 capacity 初始化 LRU 缓存
int get(int key) 如果关键字 key 存在于缓存中，则返回关键字的值，否则返回 -1 。
void put(int key, int value) 如果关键字 key 已经存在，则变更其数据值 value ；如果不存在，则向缓存中插入该组 key-value 。如果插入操作导致关键字数量超过 capacity ，则应该 逐出 最久未使用的关键字。
函数 get 和 put 必须以 O(1) 的平均时间复杂度运行。

来源：力扣（LeetCode）
链接：https://leetcode-cn.com/problems/lru-cache
著作权归领扣网络所有。商业转载请联系官方授权，非商业转载请注明出处。
 ************************************************************************/

#include<iostream>
#include<list>
#include<map>
class LRUCache {
public:
    LRUCache(int capacity) {
        _capacity=capacity;
    }
    
    int get(int key) {
        //获取key对应value _LRUlist事件复杂度O(1)；获取完毕后需要跟新最近使用的节点到_LRUlist尾
        auto it=_kItmap.find(key);
        if(it!=_kItmap.end()){
            int ret=it->second->second;
            _LRUlist.erase(it->second);
            _LRUlist.push_front({key,ret});
            _kItmap[key]=_LRUlist.begin();
            return ret;
        }
        return -1;
    }
    
    void put(int key, int value) {
        //如果_capacity不满则插入或者更新
        auto it=_kItmap.find(key);     
         if(it!=_kItmap.end()){     //若果在则直接替换        
            _LRUlist.erase(it->second);
            _kItmap.erase(key);
        }else{     //如果不再需要考虑容量是否满了
            if(_capacity<=_LRUlist.size()){
                if(_capacity){
                    _kItmap.erase(_LRUlist.back().first);
                    _LRUlist.pop_back(); 
                }    
            } 
        }
        _LRUlist.push_front({key,value});
        _kItmap[key]=_LRUlist.begin();
        //也可以直接调用list的接口single element (2)	void splice (iterator position, list& x, iterator i);
        //在position位置前插入i迭代器，这样迭代器不会失效
    }
private:
    //_LRUlist尾结点是最久最少使用，头节点是最近最多使用
    list<pair<int,int>> _LRUlist; //LRUlist---存放每个(key,value)
    unordered_map<int,list<pair<int,int>>::iterator> _kItmap;//存放每个key对应的list节点迭代器（stl节点拿不到）;unordered_map查找事件复杂度O(1)；
    size_t _capacity;
};

/**
 * Your LRUCache object will be instantiated and called as such:
 * LRUCache* obj = new LRUCache(capacity);
 * int param_1 = obj->get(key);
 * obj->put(key,value);
 */
