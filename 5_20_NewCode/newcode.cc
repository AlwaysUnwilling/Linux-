#include<iostream>
#include<string>
#include <vector>
#include <algorithm>
#define N 1000007
#include<math.h>

using namespace std;

//标题：字符串计数
/*
 *求字典序在 s1 和 s2 之间的，长度在 len1 到 len2 的字符串的个数，结果 mod 1000007。
 * */

/*
 *> **【解题思路】**
>
> 1. 循环接受收入，保证所有测试用例可以验证到
> 2. 将s1和s2补齐到len2位，因为在字典序列中s1比s2靠前，因此s1后序所有位补'a'，s2后补'z'+1
> 3. 确认s1和s2两个字符串每个字符位置上的差值
> 4. 确认len1和len2之间不同字符的个数
> 5. 注意输出时需要模1000007
 * */

int main()
{
    string s1,s2;
    int len1,len2;
    while(cin>>s1>>s2>>len1>>len2)
    {
        //将该字符串看成是26进制数，为了简单起见，将s1和s2补长到len2长度
        // 注意：s2补的是'z'+1, 因为'z' - 'a' = 25
        s1.append(len2-s1.size(),'a');
        s2.append(len2-s2.size(),(char)('z'+1));         
        // 确认s1和s2的两个字符串每个位置上的差值
        vector<int> array;
        for(int i=0;i<len2;i++){
            array.push_back(s2[i]-s1[i]);
        }
        // 确认len1和len2之间可组成的不同字符串的个数
        int result = 0;
        for(int i=len1;i<=len2;i++){
            for(int k=0;k<i;k++){
                result += array[k]*pow(26,i-1-k);
            }
        }
    //所有字符串最后都不包含是s2自身，所以最后要减1；
    cout<<(result-1)%N<<endl;
  }
  return 0;
}

//最长公共子序列
/*
 *【最长公共子序列】我们有两个字符串m和n，如果它们的子串a和b内容相同，则称a和b是m和n的公共子序列。子串中的字符不一定在原字符串中连续。
例如字符串“abcfbc”和“abfcab”，其中“abc”同时出现在两个字符串中，因此“abc”是它们的公共子序列。此外，“ab”、“af”等都是它们的字串。
现在给你两个任意字符串（不包含空格），请帮忙计算它们的最长公共子序列的长度。
 * */

int main()
{
  string m,n;
  while(cin>>m>>n){
    vector<vector<int>> vv(m.size()+1,vector<int>(n.size()+1,0));
    for(int i=1;i<m.size()+1;++i){
      for(int j=1;j<n.size()+1;++j){
        if(m[i-1]==n[j-1]){
          vv[i][j]=vv[i-1][j-1]+1;
        }else{
          vv[i][j]=max(vv[i-1][j],vv[i][j-1]);
        }
      }
    }
    cout<<vv[m.size()][n.size()]<<endl;
  }
  return 0;
}

