#include"map.hpp"
#include"set.hpp"



void MapTest()
{
    my_Map::map<int,int> m;

    m.insert(std::pair<int,int>(1,1));
    m.insert(std::make_pair(2,2));
    m.insert(std::make_pair(3,3));
    m.insert(std::make_pair(4,4));
    m.insert(std::make_pair(5,5));
    m[6]=6;
    my_Map::map<int,int>::iterator it=m.begin();
    while(it!=m.end()){
        std::cout<<it->first<<":"<<it->second<<std::endl;
        ++it;
    }
    /*my_Map::map<int,int>::const_iterator cit=m.begin();
    while(cit!=m.end()){
        std::cout<<cit->first<<":"<<cit->second<<std::endl;
        ++cit;
    }*/
    my_Map::map<int,int>::reverse_iterator rit=m.rbegin();
    while(rit!=m.rend()){
        std::cout<<rit->first<<":"<<rit->second<<std::endl;
        ++rit;
    }
}
void SetTest()
{
    my_Set::set<int> s;
    std::cout<<s.insert(1)<<std::endl;
    s.insert(9);
    s.insert(7);
    s.insert(3);
    s.insert(10);
    s.insert(8);
    s.insert(4);
    my_Set::set<int>::iterator it=s.begin();
    while(it!=s.end()){
        std::cout<<*it<<" ";
        ++it;
    }
    std::cout<<std::endl;

}
int main()
{
    MapTest();
    SetTest();
    return 0;
}
