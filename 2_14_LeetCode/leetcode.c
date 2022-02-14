/*************************************************************************
	> File Name: leetcode.c
	> Author: 
	> Mail: 
	> Created Time: Mon 14 Feb 2022 10:45:57 PM CST
    > About: 字符串相加:给定两个字符串形式的非负整数 num1 和num2 ，计算它们的和并同样以字符串形式返回。

你不能使用任何內建的用于处理大整数的库（比如 BigInteger）， 也不能直接将输入的字符串转换为整数形式。

来源：力扣（LeetCode）
链接：https://leetcode-cn.com/problems/add-strings
著作权归领扣网络所有。商业转载请联系官方授权，非商业转载请注明出处。
 ************************************************************************/

#include<iostream>
class Solution {
public:
    string addStrings(string num1, string num2) {
        string str;
        if(num1.size()==0 && num2.size()==0){
            return str;
        }
        if(num1.size()==0){
            return num2;
        }
        if(num2.size()==0){
            return num1;
        }
        auto it1=num1.rbegin();
        auto it2=num2.rbegin();
        int next=0;
        while(it1!=num1.rend() && it2!=num2.rend()){
            int tmp=(*it1-'0')+(*it2-'0')+next;
            if(tmp>9){
                tmp-=10;
                str+=tmp+'0';
                next=1;
            }else{
                str+=tmp+'0';
                next=0;
            }
            ++it1;
            ++it2;
        }
        while(it1!=num1.rend()){
            int tmp=*it1-'0'+next;
            if(tmp>9){
                tmp-=10;
                str+=tmp+'0';
                next=1;
            }else{
                str+=tmp+'0';
                next=0;
            }
            ++it1;
        }
        while(it2!=num2.rend()){
            int tmp=*it2-'0'+next;
            if(tmp>9){
                tmp-=10;
                str+=tmp+'0';
                next=1;
            }else{
                str+=tmp+'0';
                next=0;
            }
            ++it2;
        }
        if(next==1){
            str+='1';
        }
        reverse(str.begin(),str.end());
        return str;
    }
};
