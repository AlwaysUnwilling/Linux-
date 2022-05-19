#include<iostream>
#include<string>
#include<cstdlib>
#include<unistd.h>



bool GetQueryString(std::string& query_string)
{
  std::string method=getenv("METHOD");
  bool res=false;
  if("GET"==method){
    query_string=getenv("QUERY_STRING");
    res=true;
  }else if("POST"==method){
    int content_length=atoi(getenv("CONTENT_LENGTH"));
    char ch=0;
    while(content_length--){
      read(0,&ch,1);
      query_string+=ch;
    }
    res=true;
  }else{
    res=false;
  }
  return res;
}
void CutString(const std::string& in,std::string sep,std::string& s1,std::string& s2)
{
  //std::cerr<<in<<std::endl;
  size_t pos=in.find(sep);
  if(pos!=std::string::npos){
    //std::cerr<<"Pos Find"<<std::endl;
    s1=in.substr(0,pos);
    s2=in.substr(pos+sep.size());
    std::cerr<<s1<<":::"<<s2<<std::endl;
  }
}
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
