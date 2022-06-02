#pragma once 

#include<iostream>
#include<string>
#include<unistd.h>
#include<cstdlib>

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
