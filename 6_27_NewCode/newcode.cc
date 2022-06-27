#include<iostream>
#include<vector>
#include<string>
#include<algorithm>

using namespace std;

//[编程题]合唱团
/*
 *有 n 个学生站成一排，每个学生有一个能力值，牛牛想从这 n 个学生中按照顺序选取 k 名学生，要求相邻两个学生的位置编号的差不超过 d，使得这 k 个学生的能力值的乘积最大，你能返回最大的乘积吗？
 * */

//动态规划
//数据类型必须是long long类型，不然会溢出
long long getMax(vector<int>& v, int n, int k, int d)
{
	//状态F(i,j)： 以第i个人为最后一个人，总共选了j个人的最大值
	vector<vector<long long>> maxValue(n + 1, vector<long long>(k + 1, 0));
	vector<vector<long long>> minValue(n + 1, vector<long long>(k + 1, 0));

	//初始化F(i, 1): 以第i个人为最后一个人，共选了1个人的最大值
	long long ret = 0;
	for (int i = 1; i <= n; ++i)
	{
		maxValue[i][1] = minValue[i][1] = v[i - 1];
	}

	for (int i = 1; i <= n; ++i)
	{
        //需要选取k个人
		for (int j = 2; j <= k; ++j)
		{
            //约束条件：i - d <= m <= i - 1, 且不能小于1
			for (int m = i - 1; m >= max(i - d, 1); --m)
			{
				maxValue[i][j] = max(maxValue[i][j], max(maxValue[m][j - 1] * v[i - 1], minValue[m][j - 1] * v[i - 1]));
				minValue[i][j] = min(minValue[i][j], min(maxValue[m][j - 1] * v[i - 1], minValue[m][j - 1] * v[i - 1]));
			}
		}
        //更新最大值
		ret = max(ret, maxValue[i][k]);
	}
	return ret;
}
 
int main()
{
	int n, k, d;
	cin >> n;
	vector<int> v(n, 0);
	for (int i = 0; i < n; ++i)
		cin >> v[i];
	cin >> k;
	cin >> d;
	cout << getMax(v, n, k, d);
	return 0;
}

//[编程题]马戏团
/*
 *链接：https://www.nowcoder.com/questionTerminal/c2afcd7353f84690bb73aa6123548770
来源：牛客网

搜狐员工小王最近利用假期在外地旅游，在某个小镇碰到一个马戏团表演，精彩的表演结束后发现团长正和大伙在帐篷前激烈讨论，小王打听了下了解到， 马戏团正打算出一个新节目“最高罗汉塔”，即马戏团员叠罗汉表演。考虑到安全因素，要求叠罗汉过程中，站在某个人肩上的人应该既比自己矮又比自己瘦，或相等。 团长想要本次节目中的罗汉塔叠的最高，由于人数众多，正在头疼如何安排人员的问题。小王觉得这个问题很简单，于是统计了参与最高罗汉塔表演的所有团员的身高体重，并且很快找到叠最高罗汉塔的人员序列。 现在你手上也拿到了这样一份身高体重表，请找出可以叠出的最高罗汉塔的高度，这份表中马戏团员依次编号为1到N。
 * */

 struct node
{
    int _w;
    int _h;
     
    bool operator<(const node& obj)
    {
        //体重升序
        if(_w != obj._w)
            return _w <= obj._w;
        else
            //身高降序
            return _h > obj._h;
    }
};
  
int getMaxLength(vector<node>& v, int n)
{
    //首先排序
    sort(v.begin(), v.end());
    vector<int> maxLength(n, 1);
    int ret = 0;
    //求最大升序子序列的长度
    for(int i = 1; i < n; ++i)
    {
        for(int j = 0; j < i; ++j)
        {
            if(v[j]._h <= v[i]._h)
                maxLength[i] = max(maxLength[i], maxLength[j] + 1);
        }
        //更新最大值
        ret = max(ret, maxLength[i]);
    }
    return ret;
}
  
int main()
{
    int n;
     
    while(cin >> n)
    {
        vector<node> v(n);
        int num;
        //输入数据
        for(int i = 0; i < n; ++i)
            cin >> num >> v[i]._w >> v[i]._h;
         
        cout << getMaxLength(v, n) <<endl;
    }
    return 0;
}
