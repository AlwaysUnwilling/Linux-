//#pragma once 
#ifndef  __SEARCHER_H__
#define __SEARCHER_H__ 
#endif

#include<iostream>
#include<string>
#include<stdint.h>
#include<vector>
#include<unordered_map>
#include<boost/algorithm/string.hpp>
#include "cppjieba/Jieba.hpp"
//#include "limonp/Logging.hpp"

using std::string;
using std::vector;
using std::unordered_map;
using std::cout;
using std::endl;

namespace Searcher
{
  //////////////////////////////////////////////////////////////////////////////
  /////////////////////  索引模块内容    ///////////////////////////////////////
  //////////////////////////////////////////////////////////////////////////////

  //先定义一个基本索引中需要的结构 ---这个结构是正排索引的基础
  //正排索引是给定doc_id映射到文档内容(DocInfo 对象)
  struct DocInfo
  {
    int64_t doc_id;   //文档id   int64_t 是一个64位的int
    string title;
    string url;
    string content;
  };
  
  //倒排索引是给定词，映射到包含该词的文档id列表(此处不仅仅有文档id，还得有权重信息，及该词的内容)
  struct Weight
  {
    int64_t doc_id; //搜索词在哪个文档出现过
    int weight;   //对应的权重是多少---表示相关性(搜索词在文档中出现的次数---比较粗暴)
    string word;  //搜索词是什么
  };
  
  //倒排拉链
  typedef vector<Weight> InvertedList;
  //Index类用于表示整个索引结构，并且提供一些供外部调用的API
  class Index
  {
    public:
      Index();
      //查正排
      const DocInfo* GetDocInfo(int64_t doc_id);
      //查倒排
      const InvertedList* GetInvertedList(const string& key);
      //构建索引
      bool Build(const string& input_path);
      void CutWord(const string& input,vector<string>& out);
    private:
      DocInfo* BuildForward(const string& line);
      void BuildInverted(const DocInfo& doc_info);
    private:
      //索引结构
      //正排索引，数组下标就对应到doc_id
      vector<DocInfo> forward_index;
      //倒排索引，使用哈希表来表示整个映射关系
      //unordered_map<string,vector<Weight>> inverted_index;
      unordered_map<string,InvertedList> inverted_index;
      cppjieba::Jieba jieba;
  };
  
  //////////////////////////////////////////////////////////////////////////////
  /////////////////////  搜索模块内容    ///////////////////////////////////////
  //////////////////////////////////////////////////////////////////////////////
  class searcher 
  {
    private:
      Index* index;//搜索过程依赖索引，就需要一个Index的指针
    public:
      searcher():
        index(new Index())
      {}
      bool Init(const string& input_path); //初始化构建索引
      bool searchObj(const string& query,string& results);
      ~searcher()
      {
        if(index){
          delete index;
        }
      }
    private:
      string GenerateDesc(const string& content,const string& word);
  };
}//end Searcher 





