/*************************************************************************
	> File Name: leetcode.c
	> Author: 
	> Mail: 
	> Created Time: Sat 19 Feb 2022 11:27:08 PM CST
    > About:反转字符串 II:给定一个字符串 s 和一个整数 k，从字符串开头算起，每计数至 2k 个字符，就反转这 2k 字符中的前 k 个字符。

如果剩余字符少于 k 个，则将剩余字符全部反转。
如果剩余字符小于 2k 但大于或等于 k 个，则反转前 k 个字符，其余字符保持原样。

来源：力扣（LeetCode）
链接：https://leetcode-cn.com/problems/reverse-string-ii
著作权归领扣网络所有。商业转载请联系官方授权，非商业转载请注明出处。
 ************************************************************************/

#include<iostream>
class Solution {
public:
    void Reverse(string& str,int begin,int end)
    {
        while(begin<end){
            swap(str[begin],str[end]);
            ++begin;
            --end;
        }
    }
    string reverseStr(string s, int k) {
        if(s.size()==0){
            return s;
        }
        int num=s.size();
        int left=0,right=s.size()-1;
        if(num>=2*k){
            while(num/(2*k)){
                Reverse(s,left,left+k-1);
                left=left+2*k;
                num-=2*k;
            }
            if(num>k){
                Reverse(s,left,left+k-1);
            }else{
                Reverse(s,left,right);
            }
        }else if(num>=k){
            Reverse(s,left,left+k-1);
        }else{
            Reverse(s,left,right);
        }
        return s;


    }
};
