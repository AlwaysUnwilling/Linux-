/*************************************************************************
	> File Name: leetcode.c
	> Author: 
	> Mail: 
	> Created Time: Thu 24 Feb 2022 10:54:18 PM CST
    > About:电话号码的字母组合:给定一个仅包含数字 2-9 的字符串，返回所有它能表示的字母组合。答案可以按 任意顺序 返回。

给出数字到字母的映射如下（与电话按键相同）。注意 1 不对应任何字母。

来源：力扣（LeetCode）
链接：https://leetcode-cn.com/problems/letter-combinations-of-a-phone-number
著作权归领扣网络所有。商业转载请联系官方授权，非商业转载请注明出处。
 ************************************************************************/

#include<iostream>
#include<vector>
#include<string>
static char* str[]={nullptr,nullptr,"abc",
                        "def","ghi","jkl",
                        "mno","pqrs","tuv","wxyz"};
class Solution {
public:

    void _letterCombinations(vector<string>& vs,string digits,size_t i,string ret)
    {
        if(i>=digits.size()){
            vs.push_back(ret);
            return ;
        }
        for(size_t j=0;j<strlen(str[digits[i]-'0']);++j){
            char ch=*(str[digits[i]-'0']+j);
            ret+=ch;
            _letterCombinations(vs,digits,i+1,ret);
            ret.pop_back();
        }
    }
    vector<string> letterCombinations(string digits) {
        vector<string> vs;
        if(digits.size()==0){
            return vs;
        }
        string ret;
        size_t i=0;
        _letterCombinations(vs,digits,i,ret);
        return vs;
    }
};
