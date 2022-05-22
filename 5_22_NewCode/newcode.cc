#include<iostream>
#include<string>
#include<vector>
#include<stack>

using namespace std;

//标题：五子棋
/*
 *【五子棋】NowCoder最近爱上了五子棋，现在给你一个棋局，请你帮忙判断其中有没有五子连珠（超过五颗也算）。
 * */

#define N 20
  
int count(string table[], char ch, int x, int y)
{
    int maxc = 0;
    int dir[4][2][2] = { {{ -1,0 },{ 1,0 }},{{ 0,-1 },{ 0,1 }},{{ -1,-1 },{ 1,1 }},{{ -1,1 },{ 1,-1 }} };
    for (int i = 0; i < 4; ++i) // 四种方向
    {
        int c = 0;
        for (int j = 0; j < 2; ++j)  // 两个小方向
        {
            int nx = x, ny = y;
            while (nx >= 0 && nx < N && ny >= 0 && ny < N && table[nx][ny] == ch)
            {
                nx += dir[i][j][0];
                ny += dir[i][j][1];
                ++c;
            }
        }
        maxc = (maxc > c ? maxc : c);
    }
    return maxc-1; //统计两个方向（如横向的左右两个方向）的时候，当前棋子被计算了两次
}  
bool solve(string table[])
{
    // 遍历棋谱，如果某个位置有棋子，再想该位置进行搜索
    for (int i = 0; i < N; ++i)
    {
        for (int j = 0; j < N; ++j)
        {
            if (table[i][j] == '*' || table[i][j] == '+')
                // 当某个位置有连在一起的棋子，结束搜索
                if (count(table, table[i][j], i, j) >= 5)
                    return true;
        }
    }
    return false;
}  
int main()
{
    string table[N];
    while (cin >> table[0])
    {
        for (int i = 1; i < N; ++i) 
            cin >> table[i];
        cout << (solve(table) ? "Yes" : "No") << endl;
    }
    return 0;
}


//题目ID：794 Emacs计算器
/*
 *【Emacs计算器】Emacs号称神的编辑器，它自带了一个计算器。与其他计算器不同，它是基于后缀表达式的，即运算符在操作数的后面
 * */

bool IsOperator(const string& s)
{
  if(s=="+" || s=="-" || s=="*" || s=="/"){
    return true;
  }else{
    return false;
  }
}
int main()
{
  int n;
  while(cin>>n){
    vector<string> vs(n);
    for(int i=0;i<n;++i){
      cin>>vs[i];
    }
    stack<string> st;
    for(const auto& e:vs){
      if(IsOperator(e)){
        if(!st.empty()){
          int right=atoi(st.top().c_str());
          st.pop();
          int left=atoi(st.top().c_str());
          st.pop();
          if(e=="+"){
            st.push(to_string(left+right));
          }else if(e=="-"){
            st.push(to_string(left-right));
          }else if(e=="*"){
            st.push(to_string(left*right));
          }else{
            st.push(to_string(left/right));
          }
        }
      }else{
        st.push(e);
      }
    }
    cout<<st.top()<<endl;
    st.pop();
  }
  return 0;
}

