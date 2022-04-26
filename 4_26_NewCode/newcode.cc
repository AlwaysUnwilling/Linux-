#include<iostream>
#include<string>
#include<vector>

using namespace std;

//CC77 编辑距离
/*
 *给定两个单词word1和word2，请计算将word1转换为word2至少需要多少步操作。
你可以对一个单词执行以下3种操作：
a）在单词中插入一个字符
b）删除单词中的一个字符
c）替换单词中的一个字符
 * */

/*
方法：动态规划
状态：
  子状态：word1的前1，2，3，...m个字符转换成word2的前1，2，3，...n个字符需要的编辑距离 
  F(i,j):word1的前i个字符于word2的前j个字符的编辑距离
状态递推：
  F(i,j) = min { F(i-1,j）+1, F(i,j-1) +1, F(i-1,j-1) +(w1[i]==w2[j]?0:1) } 
  上式表示从删除，增加和替换操作中选择一个最小操作数
  F(i-1,j): w1[1,...,i-1]于w2[1,...,j]的编辑距离，删除w1[i]的字符--->F(i,j)
  F(i,j-1): w1[1,...,i]于w2[1,...,j-1]的编辑距离，增加一个字符--->F(i,j)
  F(i-1,j-1): w1[1,...,i-1]于w2[1,...,j-1]的编辑距离，如果w1[i]与w2[j]相同，
  不做任何操作，编辑距离不变，如果w1[i]与w2[j]不同，替换w1[i]的字符为w2[j]--->F(i,j)
初始化：
  初始化一定要是确定的值，如果这里不加入空串，初始值无法确定
  F(i,0) = i :word与空串的编辑距离，删除操作
  F(0,i) = i :空串与word的编辑距离，增加操作
返回结果：F(m,n)
*/

class Solution {
public:

    int minDistance(string word1, string word2) {
        if(word1.size()==0 || word2.size()==0) 
            return max(word1.size(),word2.size());
        

        int n=word1.size();
        int m=word2.size();
        vector<vector<int>> vv(n+1,vector<int>(m+1,0));
        for(int i=0;i<n+1;++i){
            vv[0][i]=i;
        }
        for(int i=1;i<n+1;++i){
            vv[i][0]=i;
            for(int j=1;j<m+1;++j){
              // F(i,j) = min { F(i-1,j）+1, F(i,j-1) +1, F(i-1,j-1) +(w1[i]==w2[j]?0:1) } 
              // 判断word1的第i个字符是否与word2的第j个字符相等
                if(word1[i-1]==word2[j-1]){
                    vv[i][j]=1+min(vv[i-1][j],vv[i][j-1]);
                    vv[i][j]=min(vv[i][j],vv[i-1][j-1]);
                }else{
                    vv[i][j]=1+min(vv[i][j-1],vv[i-1][j]);
                    vv[i][j]=min(vv[i][j],1+vv[i-1][j-1]);
                }
            }
        }
        return vv[n][m];
    }
};


//【公共子串计算】
/*
 *给定两个只包含小写字母的字符串，计算两个字符串的最大公共子串的长度。
注：子串的定义指一个字符串删掉其部分前缀和后缀（也可以不删）后形成的字符串
 * */

//方法：动态规划
//状态：F(i,j)表示str1前i个字符和str2前j个字符中最大公共字串的长度
//F(i,j)=if(s[i]==s[j]) F(i-1,j-1)+1;
//初始值：F(0,0)=0;F(i,0)=0;F(0,j)=0;

#include<iostream>
#include<string>
#include<vector>

using namespace std;


int GetMaxSubString(const string& str1,const string& str2)
{
    if(str1.size()==0 ||str2.size()==0) return 0;
    int n=str1.size();
    int m=str2.size();
    int maxLen=0;
    vector<vector<int>> vv(n+1,vector<int>(m,0));
    for(int i=0;i<n;++i){
        for(int j=0;j<m;++j){
            if(str1[i]==str2[j]){
                if(i<=0 || j<=0){
                    vv[i][j]=1;
                }
                else{
                    vv[i][j]=vv[i-1][j-1]+1;
                }
                if(maxLen<vv[i][j]){
                    maxLen=vv[i][j];
                }
            }
        }
    }
    return maxLen;
}
int main()
{
    string str1,str2;
    while(cin>>str1>>str2){
        cout<<GetMaxSubString(str1,str2)<<endl;
    }
    return 0;
}
