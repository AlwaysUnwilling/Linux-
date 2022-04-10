#include<iostream>
#include<string>

using namespace std;
//剑指 Offer 05. 替换空格:
//请实现一个函数，把字符串 s 中的每个空格替换成"%20"。

class Solution {
public:
    string replaceSpace(string s) {
        string ret;
        if(s.size()==0)
        {
            return ret;
        }
        size_t i=0;
        for(;i<s.size();++i)
        {
            if(s[i]!=' '){
                ret+=s[i];
            }else{
                ret+="%20";
            }
        }
        return ret;
    }
};

//剑指 Offer 58 - II. 左旋转字符串:
//字符串的左旋转操作是把字符串前面的若干个字符转移到字符串的尾部。请定义一个函数实现字符串左旋转操作的功能。比如，输入字符串"abcdefg"和数字2，该函数将返回左旋转两位得到的结果"cdefgab"。

class Solution1 {
public:
    string reverseLeftWords(string s, int n) {
        string ret;
        if(s.size()==0 || s.size()==1){
            return ret;
        }
        int count=n%s.size();
        string str1=s.substr(0,count);
        string str2=s.substr(count);
        ret+=str2;
        ret+=str1;
        return ret;
    }
};
