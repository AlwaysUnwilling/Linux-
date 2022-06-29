#include<iostream>
#include<unordered_map>
#include<vector>
#include<string>

using namespace std;

//[编程题]数组中出现次数超过一半的数字
/*
给一个长度为 n 的数组，数组中有一个数字出现的次数超过数组长度的一半，请找出这个数字。
例如输入一个长度为9的数组[1,2,3,2,2,2,5,4,2]。由于数字2在数组中出现了5次，超过数组长度的一半，因此输出2。
 * */
class Solution {
public:
    int MoreThanHalfNum_Solution(vector<int> numbers) {
        unordered_map<int, int> mp;
        for(int num : numbers)
        {
            //统计次数
            mp[num]++;
            //判断当前数据出现的次数是否超过长度的一半
            if(mp[num] > numbers.size() / 2)
                return num;
        }
        return 0;
    }
};

//[编程题]简单错误记录
/*
开发一个简单错误记录功能小模块，能够记录出错的代码所在的文件名称和行号。
处理：
1、 记录最多8条错误记录，循环记录，最后只用输出最后出现的八条错误记录。对相同的错误记录只记录一条，但是错误计数增加。最后一个斜杠后面的带后缀名的部分（保留最后16位）和行号完全匹配的记录才做算是“相同”的错误记录。
2、 超过16个字符的文件名称，只记录文件的最后有效16个字符；
3、 输入的文件可能带路径，记录文件名称不能带路径。也就是说，哪怕不同路径下的文件，如果它们的名字的后16个字符相同，也被视为相同的错误记录
4、循环记录时，只以第一次出现的顺序为准，后面重复的不会更新它的出现时间，仍以第一次为准
*/
int main()
{
    //记录错误出现的次数
    unordered_map<string, int> mp;
    //按顺序保存出现的错误
    vector<string> vec;
    //文件
    string curStr;
    //行号
    string num;
    size_t position;
    while(cin >> curStr >> num)
    {
        //文件名预处理，查看是否有\
        //rfind:  找到\, 返回非npos
        position = curStr.rfind('\\');
        if(position != string::npos)
        {
            //反斜杠存在，文件名为最后一个反斜杠之后的字符串
            curStr = curStr.substr(position + 1);
        }
        //查看文件长度是否大于16
        if(curStr.size() > 16)
            curStr = curStr.substr(curStr.size() - 16);
        //加上行号,用空格隔开
        curStr += " " + num;
        //判断记录是否为第一次出现
        if(mp.count(curStr) == 0)
            vec.push_back(curStr);
        //记录次数的累加
        mp[curStr]++;
    }
    //打印记录
    int start = 0;
    //需要打印最后8条记录
    if(vec.size() > 8)
        start = vec.size() - 8;
    for(; start < vec.size(); ++start)
    {
        cout << vec[start] << " " << mp[vec[start]] <<endl;
    }
    return 0;
}

