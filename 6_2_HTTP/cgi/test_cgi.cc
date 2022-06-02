#include<iostream>
#include"comm.hpp"


int main()
{
  std::string query_string;
  GetQueryString(query_string);
  //a=100&b=200
  std::string s1,s2;
  CutString(query_string,"&",s1,s2);
  std::string name1,value1;
  CutString(s1,"=",name1,value1);
  std::string name2,value2;
  CutString(s2,"=",name2,value2);

  std::cerr<<name1<<":"<<value1<<std::endl;
  std::cerr<<name2<<":"<<value2<<std::endl;

  //发生了重定向，打印到显示器的内容被重定向到了管道里了
  std::cout<<name1<<":"<<value1<<std::endl;
  std::cout<<name2<<":"<<value2<<std::endl;

  std::cout<<"<html>";
  std::cout<<"<head><meta charset=\"utf-8\"></head>";
  std::cout<<"<body><h3>"<<value1<<"+"<<value2<<"="<<std::to_string(atoi(value1.c_str())+atoi(value2.c_str()))<<"</h3></body>";
  std::cout<<"<body><h3>"<<value1<<"-"<<value2<<"="<<std::to_string(atoi(value1.c_str())-atoi(value2.c_str()))<<"</h3></body>";
  std::cout<<"<body><h3>"<<value1<<"*"<<value2<<"="<<std::to_string(atoi(value1.c_str())*atoi(value2.c_str()))<<"</h3></body>";
  std::cout<<"<body><h3>"<<value1<<"/"<<value2<<"="<<std::to_string(atoi(value1.c_str())/atoi(value2.c_str()))<<"</h3></body>";
  std::cout<<"</html>";
  return 0;
}
