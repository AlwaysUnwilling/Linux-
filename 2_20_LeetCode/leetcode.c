/*************************************************************************
	> File Name: leetcode.c
	> Author: 
	> Mail: 
	> Created Time: Sun 20 Feb 2022 11:40:33 PM CST
    > About:字符串相乘:给定两个以字符串形式表示的非负整数 num1 和 num2，返回 num1 和 num2 的乘积，它们的乘积也表示为字符串形式。

注意：不能使用任何内置的 BigInteger 库或直接将输入转换为整数。

来源：力扣（LeetCode）
链接：https://leetcode-cn.com/problems/multiply-strings
著作权归领扣网络所有。商业转载请联系官方授权，非商业转载请注明出处。
 ************************************************************************/

#include<iostream>
#include<string>
#include<vector>
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
    string multiply(string num1, string num2) {
        
        if(num1[0]=='0' || num2[0]=='0'){
            return "0";
        }
        vector<string> vs;
        reverse(num1.begin(),num1.end());
        reverse(num2.begin(),num2.end());
        for(int i=0;i<num1.size();++i){
            string str;
            int next=0,index=0;
            while(index<num2.size()){
                int tmp=(num1[i]-'0')*(num2[index]-'0')+next;
                if(tmp>9){
                    next=tmp/10;
                    tmp%=10;
                }else{
                    next=0;
                }
                str+=(tmp+'0');
                ++index;
            }
            if(next!=0){
                str+=(next+'0');
            }
            reverse(str.begin(),str.end());
            int count=i;
            while(count--){
                str+='0';
            }
            vs.push_back(str);
        }
        string ret;
        for(int i=0;i<vs.size();++i){
            string tmp=addStrings(ret,vs[i]);
            ret=tmp;
        }
        return ret;
    }
};
