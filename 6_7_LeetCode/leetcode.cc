#include<iostream>
#include<vector>

using namespace std;

//875. 爱吃香蕉的珂珂
/*
 *珂珂喜欢吃香蕉。这里有 n 堆香蕉，第 i 堆中有 piles[i] 根香蕉。警卫已经离开了，将在 h 小时后回来。

珂珂可以决定她吃香蕉的速度 k （单位：根/小时）。每个小时，她将会选择一堆香蕉，从中吃掉 k 根。如果这堆香蕉少于 k 根，她将吃掉这堆的所有香蕉，然后这一小时内不会再吃更多的香蕉。  

珂珂喜欢慢慢吃，但仍然想在警卫回来前吃掉所有的香蕉。

返回她可以在 h 小时内吃掉所有香蕉的最小速度 k（k 为整数）。
*/

class Solution {
public:
    int GetTime(vector<int>& piles,int speed)
    {
        int time=0;
        for(const auto& e:piles){
            //int currTime=(e+speed-1)/speed;
            //time+=currTime;
            time+=e%speed?1+e/speed:e/speed;
        }
        return time;
    }
    int minEatingSpeed(vector<int>& piles, int h) {
        int minPiles=1;
        int maxPiles=0;
        for(const auto& num:piles){
            maxPiles=max(num,maxPiles);
        }
        int k=maxPiles;
        while(minPiles<maxPiles){
            int speed=(minPiles+maxPiles)>>1;
            int time=GetTime(piles,speed);
            if(time<=h){
                k=speed;
                maxPiles=speed;
            }else{
                k=speed+1;
                minPiles=speed+1;
            }
        }
        return k;
    }
};

//剑指 Offer 33. 二叉搜索树的后序遍历序列
/*
 *输入一个整数数组，判断该数组是不是某二叉搜索树的后序遍历结果。如果是则返回 true，否则返回 false。假设输入的数组的任意两个数字都互不相同。
 * */

public:
    bool _verifyPostorder(vector<int>& postorder,int left,int right)
    {
        if(left>right){
            return true;
        }
        int root=postorder[right];
        int i=left;
        while(i<right && postorder[i]<root){
            ++i;
        }
        int big=i;
        while(i<right && postorder[i]>root){
            ++i;
        }
        if(i!=right){
            return false;
        }
        return _verifyPostorder(postorder,left,big-1) 
            && _verifyPostorder(postorder,big,right-1);
    }
    bool verifyPostorder(vector<int>& postorder) {
        if(postorder.size()==0 || postorder.size()==1){
            return true;
        }
        return _verifyPostorder(postorder,0,postorder.size()-1);
    }
};

//单调栈
#include<stack>
#include<limits.h>

class Solution {
public:
    bool verifyPostorder(vector<int>& postorder) {
        if(postorder.size()==0 || postorder.size()==1){
            return true;
        }
        int parent=INT_MAX;
        stack<int> st;
        for(int i=postorder.size()-1;i>=0;--i){
            int cur=postorder[i];
            while(!st.empty() && st.top()>cur){
                parent=st.top();
                st.pop();
            }
            if(cur>parent){
                return false;
            }else{
                st.push(cur);
            }
        }
        return true;
    }
};

