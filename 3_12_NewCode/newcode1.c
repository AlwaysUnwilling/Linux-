/*************************************************************************
	> File Name: newcode1.c
	> Author: 
	> Mail: 
	> Created Time: Sat 12 Mar 2022 10:29:41 PM CST
    > About:动态规划--拆分词句:
    描述
给定一个字符串s和一组单词dict，判断s是否可以用空格分割成一个单词序列，使得单词序列中所有的单词都是dict中的单词（序列可以包含一个或多个单词）。
例如:
给定s=“nowcode”；
dict=["now", "code"].
返回true，因为"nowcode"可以被分割成"now code".
 ************************************************************************/

#include<iostream>
class Solution {
public:
    bool wordBreak(string s, unordered_set<string> &dict) {
         if (s.empty()){
             return false;
         }
         if (dict.empty()){
             return false;
         }
         // 获取词典中的单词的最大长度
         int max_length = 0;
         unordered_set<string>::iterator dict_iter= dict.begin();
         for (; dict_iter != dict.end(); dict_iter++){
             if ((*dict_iter).size() > max_length){
                 max_length = (*dict_iter).size();
             }
         }
         vector<bool> can_break(s.size() + 1, false);
         // 初始化F(0) = true
         can_break[0] = true;
         for (int i = 1; i <= s.size(); i++){
             for (int j = i - 1; j >= 0; j--){
         // 如果最小子串长度大于max_length，跳过
                 if ((i - j) > max_length){
                 break;
                 }
         // F(i): true{j <i && F(j) && substr[j+1,i]能在词典中找到} OR false
         // 第j+1个字符的索引为j
                 if (can_break[j] && dict.find(s.substr(j, i - j)) != dict.end()){
                     can_break[i] = true;
                     break;
                 }
             }
         }
         return can_break[s.size()];
    }
};

