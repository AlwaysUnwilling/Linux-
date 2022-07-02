#include<iostream>
#include<vector>
#include<cmath>
#include<unordered_set>

using namespace std;

//DP14 最长上升子序列(一)
/*
 *描述
给定一个长度为 n 的数组 arr，求它的最长严格上升子序列的长度。
所谓子序列，指一个数组删掉一些数（也可以不删）之后，形成的新数组。例如 [1,5,3,7,3] 数组，其子序列有：[1,3,3]、[7] 等。但 [1,6]、[1,3,5] 则不是它的子序列。
我们定义一个序列是 严格上升 的，当且仅当该序列不存在两个下标 ii 和 jj 满足 i<ji<j 且 arr_i \geq arr_jarr 
i
​
 ≥arr 
j
​
 。
数据范围： 0\leq n \leq 10000≤n≤1000 , |arr_i| \le 10^9 \∣arr 
i
​
 ∣≤10 
9
  
要求：时间复杂度 O(n^2)O(n 
2
 )， 空间复杂度 O(n)O(n)
输入描述：
第一行输入一个正整数 n ，表示数组的长度 
第二行输入 n 个整数表示数组的每个元素。
输出描述：
输出最长严格上升子序列的长度
 * */

int main()
{
    int n;
    while(cin>>n){
        vector<int> v(n);
        for(int i=0;i<n;++i){
            cin>>v[i];         
        }
        vector<int> dp(n);
        for(int i=0;i<n;++i){
            dp[i]=1;
            for(int j=0;j<i;++j){
                if(v[i]>v[j]){
                    dp[i]=max(dp[i],dp[j]+1);
                }
            }
        }
        int maxLength=0;
        for(const auto& num:dp){
            if(num>maxLength){
                maxLength=num;
            }
        }
        cout<<maxLength<<endl;
    }
    return 0;
}

//BM6 判断链表中是否有环
/*
 *描述
判断给定的链表中是否有环。如果有环则返回true，否则返回false。


数据范围：链表长度 0 \le n \le 100000≤n≤10000，链表中任意节点的值满足 |val| <= 100000∣val∣<=100000
要求：空间复杂度 O(1)O(1)，时间复杂度 O(n)O(n)

输入分为两部分，第一部分为链表，第二部分代表是否有环，然后将组成的head头结点传入到函数里面。-1代表无环，其它的数字代表有环，这些参数解释仅仅是为了方便读者自测调试。实际在编程时读入的是链表的头节点。

例如输入{3,2,0,-4},1时，对应的链表结构如下图所示：

可以看出环的入口结点为从头结点开始的第1个结点（注：头结点为第0个结点），所以输出true。<Paste>
 * */


// Definition for singly-linked list.
struct ListNode {
     int val;
     ListNode *next;
     ListNode(int x) : val(x), next(NULL) {}
};

class Solution {
public:
    bool hasCycle(ListNode *head) {
        if(head==nullptr){
            return false;
        }
        unordered_set<ListNode*> st;
        ListNode* cur=head;
        while(cur){
            if(st.find(cur)==st.end()){
                st.insert(cur);
                cur=cur->next;
            }else{
                return true;
            }
        }
        return false;
    }
};
