#include<iostream>
#include<string>
#include<unordered_map>

using namespace std;
//1221. 分割平衡字符串
/*
 *在一个 平衡字符串 中，'L' 和 'R' 字符的数量是相同的。

给你一个平衡字符串 s，请你将它分割成尽可能多的平衡字符串。

注意：分割得到的每个字符串都必须是平衡字符串，且分割得到的平衡字符串是原平衡字符串的连续子串。

返回可以通过分割得到的平衡字符串的 最大数量 。
 * */

class Solution {
public:
    int balancedStringSplit(string s) {
        int cnt = 0; 
        int balance = 0; 
        for(int i = 0; i < s.size(); i++){
            if(s[i] == 'L')
                balance--; 
            if(s[i] == 'R') 
                balance++; 
            if(balance == 0) 
                cnt++; 
        }
        return cnt;
    }
};

//690. 员工的重要性
/*
 *给定一个保存员工信息的数据结构，它包含了员工 唯一的 id ，重要度 和 直系下属的 id 。

比如，员工 1 是员工 2 的领导，员工 2 是员工 3 的领导。他们相应的重要度为 15 , 10 , 5 。那么员工 1 的数据结构是 [1, 15, [2]] ，员工 2的 数据结构是 [2, 10, [3]] ，员工 3 的数据结构是 [3, 5, []] 。注意虽然员工 3 也是员工 1 的一个下属，但是由于 并不是直系 下属，因此没有体现在员工 1 的数据结构中。

现在输入一个公司的所有员工信息，以及单个员工 id ，返回这个员工和他所有下属的重要度之和。
 * */

class Solution {
public:
    int DFS(unordered_map<int,Employee*>& info, int id) 
    { 
        int curImpo = info[id]->importance; 
        for(const auto& sid : info[id]->subordinates) { 
            curImpo += DFS(info, sid);
        }
        return curImpo; 
    }
    int getImportance(vector<Employee*> employees, int id) {
        if(employees.empty()) 
            return 0; 
        unordered_map<int,Employee*> info;
        for(const auto& e : employees) {
             info[e->id] = e;
        }
        return DFS(info,id);
    }
};
