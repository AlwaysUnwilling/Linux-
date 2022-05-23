#include<iostream>
#include<string>
#include<vector>
#include<queue>

using namespace std;

//标题：解读密码
/*
 *【解读密码】nowcoder要和朋友交流一些敏感的信息，例如他的电话号码等。因此他要对这些敏感信息进行混淆，比如在数字中间掺入一些额外的符号，让它看起
来像一堆乱码。
现在请你帮忙开发一款程序，解析从nowcoder那儿接收到的信息，读取出中间有用的信息
 * */

int main()
{
  string msg;
  while(getline(cin,msg)){
    string nums;
    for(const auto& e:msg){
      if(e>='0' && e<='9'){
        nums+=e;
      }
    }
    cout<<nums<<endl;
  }
  return 0;
}

//标题：走迷宫 |
/*
 *【走迷宫】NowCoder最喜欢游乐场的迷宫游戏，他和小伙伴们比赛谁先走出迷宫。
现在把迷宫的地图给你，你能帮他算出最快走出迷宫需要多少步吗？
 * */

struct Position
{
    int x;
    int y;
    int level;   // 表示从入口到达(x,y)坐标所走的步数
};
 
// 使用广度优先遍历来走迷宫，找到最短的路径
int bfs(vector<string>& map, int m, int n)
{
    // 方向数组：下  右  左  上
    int direct[4][2] = {{1, 0},{0, 1},{0, -1},{-1, 0}};
    queue<Position> q;
    Position start{0,1,0}, out{9,8,0};
    q.push(start);
    
    vector<vector<bool>> flag(m, vector<bool>(n, false));
    while(!q.empty())
    {
        Position cur = q.front();
        q.pop();
        
        // 遍历该位置,即将该位置进行标记
        flag[cur.x][cur.y] = true;
        
        // 如果cur已经在出口的位置，说明最短路径已经找到了
        if(cur.x == out.x && cur.y == out.y)
        {
            return cur.level;
        }
        
        // 向cur四个方向继续进行遍历
        Position next;
        for(int i = 0; i < 4; ++i)
        {
            next.x = cur.x + direct[i][0];
            next.y = cur.y + direct[i][1];
            
            // 检测位置的坐标是否合法
            // 该位置是否为通路
            // 该位置如果没有遍历过
            if(next.x >= 0 && next.x < m && next.y >= 0 && next.y < n && map[next.x][next.y] == '.' && !flag[next.x][next.y])
            {
                next.level = cur.level+1;
                q.push(next);
            }
        }
    }
    
    return 0;
}
 
int main()
{
    vector<string> map(10);   // 地图
    
    // 循环输入处理每组测试用例
    int i = 0;
    while(cin>>map[i++])
    {
        if(10 == i)
        {
            // 已经将地图中的数据接收完成
            cout<<bfs(map, 10, 10)<<endl;
            i = 0;
        }
    }
    return 0;
}
