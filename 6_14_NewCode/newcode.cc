#include<iostream>
#include<vector>

using namespace std;

//WY33 计算糖果
/*
 *描述
A,B,C三个人是好朋友,每个人手里都有一些糖果,我们不知道他们每个人手上具体有多少个糖果,但是我们知道以下的信息：
A - B, B - C, A + B, B + C. 这四个数值.每个字母代表每个人所拥有的糖果数.
现在需要通过这四个数值计算出每个人手里有多少个糖果,即A,B,C。这里保证最多只有一组整数A,B,C满足所有题设条件。
 * */

bool GetABC(vector<int>& res,int a,int b,int c,int d)
{
    int A=(a+c)/2;
    int B=(b+d)/2;
    int C=B-b;
    if(a==A-B && b==B-C && c==A+B && d==B+C){
        res.push_back(A);
        res.push_back(B);
        res.push_back(C);
        return true;
    }else{
        return false;
    }
}
int main()
{
    int a,b,c,d;

    while(cin>>a>>b>>c>>d){
        vector<int> res;
        bool ret=GetABC(res,a,b,c,d);
        if(ret){
            for(int i=0;i<3;++i){
                cout<<res[i];
                if(i<2){
                    cout<<" ";
                }
            }
        }else{
            cout<<"No"<<endl;
        }
    }
    return 0;
}

//DD5 进制转换
/*
 *描述
给定一个十进制数M，以及需要转换的进制数N。将十进制数M转化为N进制数
输入描述：
输入为一行，M(32位整数)、N(2 ≤ N ≤ 16)，以空格隔开。
输出描述：
为每个测试实例输出转换后的数，每个输出占一行。如果N大于9，则对应的数字规则参考16进制（比如，10用A表示，等等）
 * */
#include<string>
#include<algorithm>

int main()
{
    int M,N;
    char map[7]={'A','B','C','D','E','F'};
    while(cin>>M>>N){
        int tmp=0;
        if(M==0){
            cout<<tmp<<endl;
            continue;
        }
        if(M<0){
            cout<<"-";
            M*=-1;
        }
        string res;
        while(M){
            tmp=M%N;
            M/=N;
            if(tmp>9){
                res+=map[tmp-10];
            }else{
                res+=tmp+'0';
            }
        }
        reverse(res.begin(),res.end());
        cout<<res<<endl;
    }
    return 0;
}


