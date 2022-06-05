#include<iostream>
#include<vector>
#include<algorithm>

using namespace std;

//[编程题]组队竞赛
/*
 *链接：https://www.nowcoder.com/questionTerminal/6736cc3ffd1444a4a0057dee89be789b?orderByHotValue=1&page=1&onlyReference=false
来源：牛客网

牛牛举办了一次编程比赛,参加比赛的有3*n个选手,每个选手都有一个水平值a_i.现在要将这些选手进行组队,一共组成n个队伍,即每个队伍3人.牛牛发现队伍的水平值等于该队伍队员中第二高水平值。
例如:
一个队伍三个队员的水平值分别是3,3,3.那么队伍的水平值是3
一个队伍三个队员的水平值分别是3,2,3.那么队伍的水平值是3
一个队伍三个队员的水平值分别是1,5,2.那么队伍的水平值是2
为了让比赛更有看点,牛牛想安排队伍使所有队伍的水平值总和最大。
如样例所示:
如果牛牛把6个队员划分到两个队伍
如果方案为:
team1:{1,2,5}, team2:{5,5,8}, 这时候水平值总和为7.
而如果方案为:
team1:{2,5,8}, team2:{1,5,5}, 这时候水平值总和为10.
没有比总和为10更大的方案,所以输出10.<Paste>
 * */

int main()
{
    int n;
    while(cin>>n){
        vector<long long> avg(3*n);
        for(int i=0;i<3*n;++i){
            cin>>avg[i];
        }
        sort(avg.begin(),avg.end());
        long long maxAvg=0;
        for(int i=3*n-2;i>=n;i-=2){
            maxAvg+=avg[i];
        }
        cout<<maxAvg<<endl;
    }
    return 0;
}

//OR63 删除公共字符
/*
 *输入两个字符串，从第一字符串中删除第二个字符串中所有的字符。例如，输入”They are students.”和”aeiou”，则删除之后的第一个字符串变成”Thy r stdnts.”
 * */

#include<string>
#include<unordered_set>

int main()
{
    string s1,s2;
    unordered_set<char> st;
    while(getline(cin,s1)){
        getline(cin,s2);
        st.clear();
        for(const auto& ch:s2){
            st.insert(ch);
        }
        string res;
        for(const auto& e:s1){
            if(st.find(e)==st.end()){
                res+=e;
            }
        }
        cout<<res<<endl;
    }
    return 0;
}
