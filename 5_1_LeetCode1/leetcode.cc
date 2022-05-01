#include<iostream>
#include<unordered_map>
#include<vector>
#include<algorithm>
#include<queue>

using namespace std;

//954. 二倍数对数组
/*
 *给定一个长度为偶数的整数数组 arr，只有对 arr 进行重组后可以满足 “对于每个 0 <= i < len(arr) / 2，都有 arr[2 * i + 1] = 2 * arr[2 * i]” 时，返回 true；否则，返回 false。
 * */


//方法一：哈希表 + 排序
class Solution {
public:
    bool canReorderDoubled(vector<int>& arr) {
        unordered_map<int,int> countMap;
        for(auto e:arr){
            countMap[e]++;
        }
        if(countMap[0]%2){   //因为0的只能与0进行匹配，因此0个数必须为偶数，否则返回false
            return false;
        }
        vector<int> tmp;
        for(auto e:countMap){
            tmp.push_back(e.first);
        }
        //对tmp进行排序
        sort(tmp.begin(),tmp.end(),[](int a,int b){return abs(a)<abs(b);});
        for(auto& e:tmp){
            if(countMap[2*e]<countMap[e]){   //若2*e的个数小于e的个数，则说明有部分e无法匹配到2*e，返回false
                return false;
            }
            countMap[2*e]-=countMap[e];
        }
        return true;
    }
};

//方法二：队列:
// 对数组进行排序：遍历数组每个元素与队头的元素进行比较，如果匹配则pop掉队头元素，不匹配入队
// 遍历完成后判断队中是否为空。
class Solution {
public:
    bool canReorderDoubled(vector<int>& arr) {
        sort(arr.begin(), arr.end());
        queue<int> q;
        for(int e : arr)
        {
            if(q.empty()) q.push(e);
            else if(e * 2 == q.front() || q.front() * 2 == e) q.pop();
            else q.push(e);
        }
        return q.empty();
    }
};

//744. 寻找比目标字母大的最小字母
/*
 *给你一个排序后的字符列表 letters ，列表中只包含小写英文字母。另给出一个目标字母 target，请你寻找在这一有序列表里比目标字母大的最小字母。

在比较时，字母是依序循环出现的。举个例子：

如果目标字母 target = 'z' 并且字符列表为 letters = ['a', 'b']，则答案返回 'a'
 * */

//方法一：线性查找
class Solution {
public:
    char nextGreatestLetter(vector<char>& letters, char target) {
        char ret=letters[0];
        for(auto& e:letters){
            if(e>target){
                ret=e;
                break;
            }
        }
        return ret;
    }
};

//方法二：二分查找
class Solution {
public:
    char nextGreatestLetter(vector<char>& letters, char target) {
        if(letters[0]>target || letters[letters.size()-1]<target) return letters[0];
        int left=0;
        int right=letters.size()-1;
        int ret=0;
        while(left<=right){
            int index=((left+right)>>1);
            if(letters[index]<=target){
                left=index+1;
            }else{
                ret=index;
                right=index-1;
            }
        }
        return letters[ret];
    }
};

