#include<iostream>
#include<string>
#include<set>
#include<vector>

using namespace std;
//804. 唯一摩尔斯密码词
//国际摩尔斯密码定义一种标准编码方式，将每个字母对应于一个由一系列点和短线组成的字符串
//为了方便，所有 26 个英文字母的摩尔斯密码表如下：
//[".-","-...","-.-.","-..",".","..-.","--.","....","..",".---","-.-",".-..","--","-.","---",".--.","--.-",".-.","...","-","..-","...-",".--","-..-","-.--","--.."]

class Solution {
public:
    const char* mosArr[27]={nullptr,".-","-...","-.-.","-..",".",
                            "..-.","--.","....","..",".---",
                            "-.-",".-..","--","-.","---",".--.",
                            "--.-",".-.","...","-","..-","...-",
                            ".--","-..-","-.--","--.."};
    int uniqueMorseRepresentations(vector<string>& words) {
        if(words.size()==0){
            return 0;
        }
        std::set<string> s;
        for(auto& e:words){
            string str;
            for(size_t i=0;i<e.size();++i){
                str+=mosArr[e[i]-'a'+1];
            }
            s.insert(str);
        }
        return s.size();
    }
};

