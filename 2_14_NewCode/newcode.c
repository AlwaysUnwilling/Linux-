/*************************************************************************
	> File Name: newcode.c
	> Author: 
	> Mail: 
	> Created Time: Mon 14 Feb 2022 10:18:28 PM CST
    > About:把字符串转换成整数:描述
将一个字符串转换成一个整数，要求不能使用字符串转换整数的库函数。 数值为 0 或者字符串不是一个合法的数值则返回 0

数据范围：字符串长度满足 0 \le n \le 100 \0≤n≤100 
进阶：空间复杂度 O(1) \O(1)  ，时间复杂度 O(n) \O(n) 

注意：
①字符串中可能出现任意符号，出现除 +/- 以外符号时直接输出 0
②字符串中可能出现 +/- 且仅可能出现在字符串首位。
输入描述：
输入一个字符串,包括数字字母符号,可以为空
返回值描述：
如果是合法的数值表达则返回该数字，否则返回0
 ************************************************************************/

#include<iostream>
class Solution {
public:
    int StrToInt(string str) {
        if(str.size()==0){
            return 0;
        }
        int ret=0;
        if(str[0]>='0' && str[0]<='9'){
            for(auto ch:str){
                if(ch<'0' || ch>'9'){
                    return 0;
                }
                ret*=10;
                ret+=ch-'0';
            }
        }else if(str[0]=='+' || str[0]=='-'){
            int flag=1;
            if(str[0]=='-'){
                flag=-1;
            }
            for(size_t i=1;i<str.size();++i){
                if(str[i]<'0' || str[i]>'9'){
                    return 0;
                }
                ret*=10;
                ret+=str[i]-'0';
            }
            ret*=flag;
        }
        return ret;
    }
};
