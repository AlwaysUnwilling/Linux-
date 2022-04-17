#include<iostream>
#include<unordered_map>
#include<unordered_set>
#include<string>

using namespace std;

//819. 最常见的单词
/*
 *给定一个段落 (paragraph) 和一个禁用单词列表 (banned)。返回出现次数最多，同时不在禁用列表中的单词。

题目保证至少有一个词不在禁用列表中，而且答案唯一。

禁用列表中的单词用小写字母表示，不含标点符号。段落中的单词不区分大小写。答案都是小写字母。
 * */

class Solution {
public:
    string mostCommonWord(string paragraph, vector<string>& banned) {
        unordered_map<string,int> words;
        unordered_set<string> banWords;
        if(banned.size()!=0){
            for(auto& e:banned){
                banWords.insert(e);
            }
        }
        string tmp;
        int maxCount=0;
        for(auto e:paragraph){
            if((e>='a' && e<='z') || (e>='A' && e<='Z')){
                if(e>='A' && e<='Z'){
                    e+=32;
                }
                tmp+=e;
            }else{
                if(tmp.size()!=0 && (banWords.size()==0 || banWords.find(tmp)==banWords.end())){
                    words[tmp]++;
                }
                tmp.clear();
            }
        }
        if(tmp.size()!=0){
            words[tmp]++;
        }
        string ret;
        for(auto& e:words){
            if(maxCount<e.second){
                maxCount=e.second;
                ret=e.first;
            }
        }
        return ret;
    }
};

//53. 最大子数组和:
/*
 *给你一个整数数组 nums ，请你找出一个具有最大和的连续子数组（子数组最少包含一个元素），返回其最大和。

子数组 是数组中的一个连续部分。
 * */

//动态规划

class Solution {
public:
    int maxSubArray(vector<int>& nums) {
        if(nums.size()==1){
            return nums[0];
        }
        int n=nums.size();
        for(int i=1;i<n;++i){
            nums[i]=max(nums[i],nums[i-1]+nums[i]);
        }
        int max=INT_MIN;
        for(auto e:nums){
            if(e>max){
                max=e;
            }
        }
        return max;
    }
};
