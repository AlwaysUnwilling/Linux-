#include<iostream>
#include<vector>

using namespace std;

//[编程题]排序子序列
/*
牛牛定义排序子序列为一个数组中一段连续的子序列,并且这段子序列是非递增或者非递减排序的。牛牛有一个长度为n的整数数组A,他现在有一个任务是把数组A分为若干段排序子序列,牛牛想知道他最少可以把这个数组分为几段排序子序列.
如样例所示,牛牛可以把数组A划分为[1,2,3]和[2,2,1]两个排序子序列,至少需要划分为2个排序子序列,所以输出2<Paste>
 * */

int main()
{
    int n;
    while(cin>>n){
        if(n==1){
            cout<<1<<endl;
            continue;
        }
        vector<long long> v(n);
        for(int i=0;i<n;++i){
            cin>>v[i];
        }
        int ret=0;
        int end=0;
        while(end<n-1){
            while(end<n-1 && v[end]==v[end+1]){
                end++;
            }
            if(end<n-1 && v[end]<v[end+1]){
                ret++;
                while(end<n-1 && v[end]<=v[end+1]){
                    end++;
                }
                end++;
            }
            while(end<n-1 && v[end]==v[end+1]){
                end++;
            }
            if(end<n-1 && v[end]>v[end+1]){
                ret++;
                while(end<n-1 && v[end]>=v[end+1]){
                    end++;
                }
                end++;
            }
        }
        if(end==n-1){
            ret++;
        }
        cout<<ret<<endl;
    }
    
    return 0;
}

#include<stack>
#include<string>

//OR62 倒置字符串
/*
 *将一句话的单词进行倒置，标点不倒置。比如 I like beijing. 经过函数后变为：beijing. like I
 * */

int main()
{
    string str;
    while(getline(cin,str)){
        string ret;
        stack<string> st;
        string tmp;
        for(int i=0;i<str.size();++i){
            if(str[i]!=' '){
                tmp+=str[i];
            }else{
                st.push(tmp);
                tmp.clear();
            }
            if(i==str.size()-1){
                st.push(tmp);
                break;
            }
        }
        while(!st.empty()){
            ret+=st.top();
            st.pop();
            if(st.size()!=0){
                ret+=' ';
            }
        }
        cout<<ret<<endl;     
    }
    return 0;
}

