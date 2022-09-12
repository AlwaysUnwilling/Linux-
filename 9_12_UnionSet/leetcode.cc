#include<iostream>
#include<vector>

using namespace std;
//剑指 Offer II 116. 省份数量
/*
 *有 n 个城市，其中一些彼此相连，另一些没有相连。如果城市 a 与城市 b 直接相连，且城市 b 与城市 c 直接相连，那么城市 a 与城市 c 间接相连。

省份 是一组直接或间接相连的城市，组内不含其他没有相连的城市。

给你一个 n x n 的矩阵 isConnected ，其中 isConnected[i][j] = 1 表示第 i 个城市和第 j 个城市直接相连，而 isConnected[i][j] = 0 表示二者不直接相连。

返回矩阵中 省份 的数量。
 * */

//方法一：实现并查集
template<typename T>
class UnionSet
{
public:
	UnionSet(size_t n)
		:_us(n,-1)
	{}
	void UnionToSet(int x1, int x2)
	{
		int root1 = FindRoot(x1);
		int root2 = FindRoot(x2);
		if (root1 != root2) {
			_us[root1] += _us[root2];   //将root2合并到root上
			_us[root2] = root1;              //root2更新父节root1
		}
	}
	int FindRoot(int x)
	{
		while (_us[x] >= 0) {
			x = _us[x];
		}
		//压缩路径
		return x;
	}
	bool IsInSet(int x1,int x2)
	{
		return FindRoot(x1) == FindRoot(x2);
	}
    size_t SetSize()
    {
        size_t size=0;
        for(auto root:_us){
            if(root < 0){
                size++;
            }
        }
        return size;
    }
private:
	std::vector<T> _us;
};
class Solution {
public:
    int findCircleNum(vector<vector<int>>& isConnected) {
        UnionSet<int> us(isConnected.size());
        for(size_t i=0;i < isConnected.size();++i){
            for(size_t j=0;j < isConnected[i].size();++j){
                if(isConnected[i][j]==1){
                    us.UnionToSet(i,j);
                }
            }
        }

        return us.SetSize();
    }
};

//方法二：模拟并查集
class Solution {
public:
    int findCircleNum(vector<vector<int>>& isConnected) {
        vector<int> ufs(isConnected.size(),-1);
        auto findRoot=[&ufs](int x)
        {
            while(ufs[x] >= 0){
                x=ufs[x];
            }
            return x;
        };
        for(int i=0;i < isConnected.size();++i){
            for(int j=0;j < isConnected[0].size();++j){
                if(isConnected[i][j] == 1){
                    int root1=findRoot(i);
                    int root2=findRoot(j);
                    if(root1 != root2){
                        ufs[root1]+=ufs[root2];
                        ufs[root2]=root1;
                    }
                }
            }
        }
        int size=0;
        for(const auto root:ufs){
            if(root < 0){
                size++;
            }
        }
        return size;
    }
};

//990. 等式方程的可满足性
/*
 *给定一个由表示变量之间关系的字符串方程组成的数组，每个字符串方程 equations[i] 的长度为 4，并采用两种不同的形式之一："a==b" 或 "a!=b"。在这里，a 和 b 是小写字母（不一定不同），表示单字母变量名。

只有当可以将整数分配给变量名，以便满足所有给定的方程时才返回 true，否则返回 false。 
 * */

class Solution {
public:
    bool equationsPossible(vector<string>& equations) {
        vector<int> us(26,-1);
        auto findRoot=[&us](int x)
        {
            while(us[x]>=0){
                x=us[x];
            }
            return x;
        };
        for(const auto str:equations){
            if(str[1]=='='){
                int root1=findRoot(str[0]-'a');
                int root2=findRoot(str[3]-'a');
                if(root1!=root2){
                    us[root1]+=us[root2];
                    us[root2]=root1;
                }

            }
        }
        for(const auto str:equations){
            if(str[1]=='!'){
                int root1=findRoot(str[0]-'a');
                int root2=findRoot(str[3]-'a');
                if(root1==root2){
                    return false;
                }
            }
        }
        return true;
    }
};
