#include<iostream>
#include<vector>
#include<list>
#include<queue>
#include<stdlib.h>
#include<algorithm>
#include<stack>
#include<functional>   //仿函数头文件

using namespace std;
#include"priority_queue.h"
void test_priority_queue()  //不支持迭代器遍历
{
	//priority_queue<int> pq;  //默认是大的优先级高
	priority_queue<int,vector<int>,greater<int>> pq;  //默认是大的优先级高,如果需要小的优先级高如何操作？ 仿函数
	pq.push(3);
	pq.push(1);
	pq.push(9);
	pq.push(4);
	pq.push(2);
	while (!pq.empty())
	{
		cout << pq.top()<<" ";
		pq.pop();
	}
	cout << endl;
}
//仿函数的其他应用
void test_sort()
{
	vector<int> v;
	v.push_back(2);
	v.push_back(7);
	v.push_back(1);
	v.push_back(6);
	v.push_back(0);
	for (auto e : v)
	{
		cout << e << " ";
	}
	cout << endl;
	sort(v.begin(), v.end());   //默认拍的是升序(less)
	for (auto e : v)
	{
		cout << e << " ";
	}
	cout << endl;sort(v.begin(), v.end(), greater<int>());
	for (auto e : v)
	{
		cout << e << " ";
	}
	cout << endl;
}
int main()
{
	//test_priority_queue();
	//my_priority_queue::test_priority_queue();
	/*my_priority_queue::less<int> lessFunc;   
	cout << lessFunc(1, 2) << endl;*/
	test_sort();
	return 0;
}
