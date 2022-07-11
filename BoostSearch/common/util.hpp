#ifndef __UTIL_HPP__
#define __UTIL_HPP__ 
#endif 

#include<iostream>
#include<string>
#include<unordered_map>
#include<vector>
#include<fstream>
#include<boost/algorithm/string.hpp>

using std::string;
using std::cout;
using std::endl;
using std::vector;
using std::unordered_map;

namespace Common
{
  class Util 
  {
  public:
  //负责从指定的路径中读取文件的整体内容，并将内容写入到output中
    static bool Read(const string& input_path,string& output)
    {
      std::ifstream file(input_path.c_str());
      if(!file.is_open()){
        return false;
      }
      //读取整个文件内容，按行读取，把读到的内容追加到output中
      //getline按行读取文件中的一行，成功则把结果放在line中，返回true；读取失败(文件末尾)，返回false
      string line;
      while(std::getline(file,line)){
        output+=(line+"\n");
      }
      file.close();
      return true;
    }
    //机遇boost中字符串切分，封装一下
    static void Split(const string& input,const string& delimiter,vector<string>& output)
    {
      boost::split(output,input,boost::is_any_of(delimiter),boost::token_compress_off);
    }
  };
} //namespace common 
