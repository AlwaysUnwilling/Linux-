/*************************************************************************
	> File Name: leetcode.c
	> Author: 
	> Mail: 
	> Created Time: Fri 18 Feb 2022 10:08:18 PM CST
    > About:字符串最后一个单词的长度:描述
计算字符串最后一个单词的长度，单词以空格隔开，字符串长度小于5000。（注：字符串末尾不以空格为结尾）
输入描述：
输入一行，代表要计算的字符串，非空，长度小于5000。

输出描述：
输出一个整数，表示输入字符串最后一个单词的长度。
 ************************************************************************/

#include<iostream>
#include<string>



int main()
{
    std::string str;
    str.clear();
    int count =0;
    std::getline(std::cin,str);
    size_t s=str.rfind(' ');
    if(s!=std::string::npos){
        for(size_t i=s+1;i<str.size();++i){
            count++;
        }
        std::cout<<count<<std::endl;
    }else{
        std::cout<<str.size()<<std::endl;
    }
    return 0;
}
