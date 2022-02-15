#include"unordered_map.hpp"
#include"unordered_set.hpp"



void Test_Unordered_Map()
{
    my_Hash::unordered_map<int, int> m;
    m.insert(std::make_pair(1, 1));
    m.insert(std::make_pair(2, 2));
    m.insert(std::make_pair(3, 3));
    m.insert(std::make_pair(4, 4));
    my_Hash::unordered_map<int, int>::iterator it = m.begin();
	while (it != m.end()){
        std::cout << it->first << ":" << it->second << std::endl;
		++it;
	}
    std::cout<<std::endl;
    my_Hash::unordered_map<std::string, std::string> dict;
    dict.insert(std::make_pair("sort", "排序"));
    dict.insert(std::make_pair("string", "字符串"));
    dict.insert(std::make_pair("hello", "你好"));
    dict.insert(std::make_pair("world", "世界"));
	dict["int"] = "整型";
    my_Hash::unordered_map<std::string, std::string>::iterator dit = dict.begin();
	while (dit != dict.end())
	{
        std::cout << dit->first << ":" << dit->second << std::endl;
		++dit;
	}
    std::cout <<std::endl;
}
int main()
{
    my_Hash::unordered_map<int,int> um;
    my_Hash::unordered_set<int> us;
    us.insert(5);
    us.insert(6);
    us.insert(3);
    us.insert(2);
    us.insert(5);
    us.insert(7);
    auto it=us.begin();
    while(it!=us.end()){
        std::cout<<*it<<" ";
        ++it;
    }
    std::cout<<std::endl;
    
    um.insert(std::make_pair(2,2));
    um.insert(std::make_pair(3,3));
    um.insert(std::make_pair(4,4));
    um.insert(std::make_pair(5,5));
    um.insert(std::make_pair(7,7));
    um.insert(std::make_pair(6,6));
    um.insert(std::make_pair(7,8));
    
    my_Hash::unordered_map<int,int> um1(um);
    my_Hash::unordered_map<int,int> um2;
    um2=um1;
    Test_Unordered_Map();
    return 0;
}
