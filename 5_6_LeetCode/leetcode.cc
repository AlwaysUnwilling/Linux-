#include<iostream>
#include<queue>


using namespace std;

//933. 最近的请求次数
/*
 *写一个 RecentCounter 类来计算特定时间范围内最近的请求。

请你实现 RecentCounter 类：

RecentCounter() 初始化计数器，请求数为 0 。
int ping(int t) 在时间 t 添加一个新请求，其中 t 表示以毫秒为单位的某个时间，并返回过去 3000 毫秒内发生的所有请求数（包括新请求）。确切地说，返回在 [t-3000, t] 内发生的请求数。
保证 每次对 ping 的调用都使用比之前更大的 t 值。
 * */

//我们可以用一个队列维护发生请求的时间，当在时间t收到请求时，将时间t入队，当队头的时间小于
//t-3000时出队，即，q.front()<t-3000
class RecentCounter {
public:
    RecentCounter() {

    }
    
    int ping(int t) {
        q.push(t);
        while(q.front()<t-3000){
            q.pop();
        }
        return q.size();
    }
    queue<int> q;
};

/**
 * Your RecentCounter object will be instantiated and called as such:
 * RecentCounter* obj = new RecentCounter();
 * int param_1 = obj->ping(t);
 */ 

//713. 乘积小于 K 的子数组
/*
 *给你一个整数数组 nums 和一个整数 k ，请你返回子数组内所有元素的乘积严格小于 k 的连续子数组的数目。
 * */


//滑动窗口
//固定[i,j]数组的右端j的位置，则左端i越大，子数组的乘积越小。
class Solution {
public:
    int numSubarrayProductLessThanK(vector<int>& nums, int k) {
        int n = nums.size(), ret = 0;
        int prod = 1, i = 0;
        for (int j = 0; j < n; j++) {
            prod *= nums[j];
            while (i <= j && prod >= k) {
                prod /= nums[i];
                i++;
            }
            ret += j - i + 1;
        }
        return ret;
    }
};
