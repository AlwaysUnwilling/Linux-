#include"searcher.h"
#include"../common/util.hpp"
#include<algorithm>
#include<jsoncpp/json/json.h>

namespace Searcher 
{

  const char* const DICT_PATH = "../jieba_dict/jieba.dict.utf8";
  const char* const HMM_PATH = "../jieba_dict/hmm_model.utf8";
  const char* const USER_DICT_PATH = "../jieba_dict/user.dict.utf8";
  const char* const IDF_PATH = "../jieba_dict/idf.utf8";
  const char* const STOP_WORD_PATH = "../jieba_dict/stop_words.utf8";
  Index::Index()
    :jieba(DICT_PATH,HMM_PATH,USER_DICT_PATH,IDF_PATH,STOP_WORD_PATH)
  {}
  const DocInfo* Index::GetDocInfo(int64_t doc_id)
  {
    if(doc_id<0 || doc_id>=forward_index.size()){
      return nullptr;
    }
    return &forward_index[doc_id];
  }
  const InvertedList* Index::GetInvertedList(const string& key)
  {
    unordered_map<string,InvertedList> ::iterator it=inverted_index.find(key);
    if(it==inverted_index.end()){
      return nullptr;
    }
    return &it->second;
  }
  bool Index::Build(const string& input_path)
  {
    //1、按行读取输入文件内容(上个环节中预处理模块生成的raw_input文件)
    //raw_input文件结构：是一个行文本文件，每一行对应一个文档
    //每一行又分成三个部分，使用'\3'来切分:标题、url、正文
    cout<<"开始构建索引..."<<endl;
    std::ifstream file(input_path.c_str());
    if(!file.is_open()){
      cout<<"构建索引文件打开失败"<<endl;
      return false;
    }
    string line;
    while(std::getline(file,line)){
      //2、针对当前行，解析成DocInfo对象，并构造为正排索引
      DocInfo* doc_info=BuildForward(line);
      if(doc_info==nullptr){
        //当前文档构造正排出现问题
        cout<<"构建正排失败"<<endl;
        continue;
      }
      //3、根据当前的DocInfo对象，进行解析，构造成倒排索引
      BuildInverted(*doc_info);
      if(doc_info->doc_id%100==0){
        cout<<doc_info->doc_id<<endl;
      }
    }
    cout<<"结束构建索引..."<<endl;
    file.close();
    return true;
  }
  DocInfo* Index::BuildForward(const string& line)
  {
    //1、先把line按照'\3'切分成3个部分
    vector<string> tokens;
    Common::Util::Split(line,"\3",tokens);
    if(tokens.size()!=3){
      //如果切分结果不是3份，就认为当前文档构造失败
      return nullptr;
    }
    //2、把切分结构填充到DocInfo对象中
    DocInfo doc_info;
    doc_info.doc_id=forward_index.size();
    doc_info.title=tokens[0];
    doc_info.url=tokens[1];
    doc_info.content=tokens[2];
    forward_index.push_back(std::move(doc_info));
    //3、返回结果
    //注意这里不能返回doc_info的地址---会导致野指针问题！！！！
    return &forward_index.back();
  }

  void Index::CutWord(const string& input,vector<string>& out)
  {
    jieba.CutForSearch(input,out);
  }
  void Index::BuildInverted(const DocInfo& doc_info)
  {
    //倒排是一个哈希表
    //key是词(针对文档的粉刺结果)
    //value是倒排拉链(包含若干个Weight对象)
    //每次遍历到一个文档，就要分析这个文档，并且把相关信息更新到倒排结构中
    //**一般而言标题中出现的搜索词的次数相关性更强，因此我们
    //约定 权重=标题中出现的次数*10+正文出现的次数
    
    //0、创建一个专门统计词频的结构
    struct WordCut
    {
      int title_cnt;
      int content_cnt;
      WordCut()
        :title_cnt(0),
        content_cnt(0)
      {}
    };
    unordered_map<string,WordCut> word_cnt_map;
    //1、针对标题进行分词
    vector<string> title_token;
    CutWord(doc_info.title,title_token);
    //2、遍历分词结果，统计每个词出现的次数
    //注意：此处需要考虑大小写问题
    //统计之前先把单词全部转成小写/大写
    for(string word:title_token){
      boost::to_lower(word);
      ++word_cnt_map[word].title_cnt;
    }
    //3、针对正文进行分词
    vector<string> content_token;
    CutWord(doc_info.content,content_token);
    //4、遍历分词结果，统计每个分词出现的次数
    for(string word:content_token){
      boost::to_lower(word);
      ++word_cnt_map[word].content_cnt;
    }
    //5、根据遍历结果，整合出Weight对象，并把结果更新到倒排索引中即可
    for(const auto& word_pair:word_cnt_map){
      //构造Weight对象
      Weight weight;
      weight.doc_id=doc_info.doc_id;
      weight.weight=word_pair.second.title_cnt*10+word_pair.second.content_cnt;
      weight.word=word_pair.first;
      
      InvertedList& invertedlist=inverted_index[word_pair.first];
      invertedlist.push_back(std::move(weight));
    }
  }

  ///////////////////////////////////////////////////////
  //////////////////   searcher  ////////////////////////
  ///////////////////////////////////////////////////////
  
    bool searcher::Init(const string& input_path) //初始化构建索引
    {
      
      return index->Build(input_path);
    }

    //查询词进行搜索，得到结果
    bool searcher::searchObj(const string& query,string& output)
    {
      //1、[分词] 针对查询词进行分词
      vector<string> tokens;
      index->CutWord(query,tokens);
      //2、[触发] 根据分词结果，查倒排，把相关文档都或得
      vector<Weight> all_token_results;
      for(string word:tokens){
        //构建索引时已经把单词的大小写忽略了(全部处理成了小写)
        //因此在查倒排时也需要将word全部转换为小写
        boost::to_lower(word);
        auto* invertedlist=index->GetInvertedList(word);
        if(invertedlist==nullptr){
          //该词在倒排索引中不存在---如果该词在所有文档中都不存在，
          //则得到的倒排拉链即为空
          continue;
        }
        //tokens包含了多个结果，需要把多个结果合并到一起，才能进行统一的排序
        all_token_results.insert(all_token_results.end(),invertedlist->begin(),
            invertedlist->end());
      }
      //3、[排序] 把刚才查到的文档的倒排拉链合并到一起并按照权重进行降序排序
      std::sort(all_token_results.begin(),all_token_results.end(),
          [](const Weight& w1,const Weight& w2){
          return w1.weight > w2.weight;
          }); 
      //4、[包装结果] 把得到的这些倒排拉链中的文档ID获得到，然后去查正排
      //              再把doc_info中的内容构造成最终预期的格式
      //最终的格式：每个结果都包含--标题、url、描述(正文摘要信息，里面包含了
      //            查询词/查询词的一部分),组织成特定格式的字符串(JSON)
      //  使用jsoncpp这个库来实现json的操作
      //需要使用的一个核心类 Json::Value；这个类就表示了一个json对象，
      //该对象是一个键值对结构，使用Json::Value对象的时候就可以把它当成是
      //一个map来使用/有时也可以当成一个vector
      Json::Value results; //包含了若干个搜索结果，每个搜索结果就是一个Json对象
      for(const auto& weight:all_token_results){
        //根据weight中的doc_id查正排
        const DocInfo* doc_info=index->GetDocInfo(weight.doc_id);
        //把这个doc_info对象再进一步包装成一个JSON对象
        Json::Value result;
        result["title"]=doc_info->title;
        result["url"]=doc_info->url;
        result["desc"]=GenerateDesc(doc_info->content,weight.word);
        results.append(result);
      }
      //最后一步，把得到的results这个JSON对象序列化成字符串，写入到output中
      Json::FastWriter writer;
      output=writer.write(results);
      return true;
    }
    string searcher::GenerateDesc(const string& content,const string& word)
    {
      //根据正文找到word出现的位置
      //以该位置为中心，向前找60个字节，作为描述的起始位置，
      //再从起始位置向后找160个字节作为整个描述
      //需要注意边界条件：
      //  如果前面不够60个字节，就从0开始
      //  如果后面内容不够了，就到末尾结束
      //  如果后面的内容显示不下了，可以使用"..."省略号来表示
      

      //1、先找到word在正文中出现的位置
      size_t first_pos=content.find(word);
      size_t desc_pos = 0;
      if(first_pos == string::npos){
        //该词在正文中不存在(该词只出现在标题中)
        //如果找不到直接从头开始作为起始描述位置
        if(content.size() < 160){
          return content;
        }
        string desc=content.substr(desc_pos,160);
        desc[desc.size()-1]='.';
        desc[desc.size()-2]='.';
        desc[desc.size()-3]='.';
        return desc;
      }
      //找到了 以此位置往前找60字节
      desc_pos = first_pos < 60 ? 0 : first_pos - 60;
      if(desc_pos+160 >= content.size()){
          return content.substr(desc_pos);
      }else{
        string desc=content.substr(desc_pos,160);
        desc[desc.size()-1]='.';
        desc[desc.size()-2]='.';
        desc[desc.size()-3]='.';
        return desc;
      }
    }
}// end namespace Searcher 


