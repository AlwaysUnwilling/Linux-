/*
 *这个代码用于实现预处理模块；核心功能就是需要读取并分析boost文档的.html内容；
 解析出每个文档的标题，url，正文(去除html标签)；
 最终把结果输出成一个行文本文件
 * */

#include<iostream>
#include<string>
#include<unordered_map>
#include<vector>
#include<boost/filesystem/path.hpp>
#include<boost/filesystem/operations.hpp>
#include"../common/util.hpp"

using std::cout;
using std::endl;
using std::string;
using std::unordered_map;
using std::vector;


//定义一些相关变量和结构体

string g_input_path="../data/input/boost_1_53_0/doc/html";  //读取boost文档的html路径
string g_output_path="../data/tmp/raw_input";   //预处理模块输出结果存放路径
//创建一个重要的结构体，表示一个文档(一个html)
struct DocInfo
{
  string title; //文档标题
  string url;   //文档url
  string content; //文档的正文
};

//预处理核心流程
//1、把input目录中的所有的html路径都枚举出来
//2、再去根据枚举出来的路径依次读取每个文件内容，并进行解析
//3、把解析结果写入到最终的输出文件中

bool EnumFile(const string& input_path,vector<string>& file_list)
{
  //枚举路径需要使用boost来完成(or c++17)
  //boost 大部分功能都是包含头文件就能使用，无需连接库文件，但是filesystem模块的功能还是需要连接上库的
  //把boost::filesystem 这个命名空间定义一个别名
  namespace fs=boost::filesystem;
  fs::path root_path(input_path);
  if(!fs::exists(root_path)){
    cout<<"当前目录不存在"<<endl;
    return false;
  }
  //递归遍历的时候使用到的一个核心类(迭代器),在使用循环实现的时就可以自动实现递归
  fs::recursive_directory_iterator end_iter;//C++中通常使用无参构造会构造出的迭代器默认
                                          //指向最后一个元素的下一个元素
  for(fs::recursive_directory_iterator beg_iter(root_path);beg_iter!=end_iter;++beg_iter){
    //判定：当前的路径对应的是不是一个普通文件，如果是目录，直接跳过
    if(!fs::is_regular_file(*beg_iter)){
      continue;
    }
    //如果是其他文件(不是html文件)直接跳过;只需要获取html文件
    if(beg_iter->path().extension()!=".html") {
      continue;
    }
    //把得到的路径加到file_list中
    file_list.push_back(beg_iter->path().string());
  }
  return true;
}

//找到html中的title标签
bool ParseTitle(const string& html,string& title)
{
  size_t beg=html.find("<title>");
  if(beg==string::npos){
    cout<<"标题未找到"<<endl;
    return false;
  }
  size_t end=html.find("</title>");
  if(end==string::npos){
    cout<<"标题未找到"<<endl;
    return false;
  }
  beg+=string("<title>").size();
  if(beg>=end){
    cout<<"标题不合法"<<endl;
    return false;
  }
  title=html.substr(beg,end-beg);
  return true;
}
//根据本地路径获取到在线文档路径：
//本地路径：../data/input/boost_1_53_0/doc/html/thread.html 
//在线路径：https://www.boost.org/doc/libs/1_53_0/doc/html/thread.html 
//把本地路径的后半部分截取出来，再拼接上在线路径的前缀即可
bool ParsePath(const string& file_path,string& url)
{
  string url_head="https://www.boost.org/doc/libs/1_53_0/doc/html";
  string url_tail=file_path.substr(g_input_path.size());
  url=url_head+url_tail;
  //cout<<url<<endl;
  return true;
}
//针对读取出来的html内容进行去标签
//以"<"">"未标记进行具体的判断；按照逐字符的方式读取内容；
//引入一个bool标志位，表示当前是html标签还是正文
//如果是"<"则说明接下来的内容就是标签，则忽略掉标签内容
//如果是">"则说明接下来的是正文，则把正文写入到结果中
bool ParseContent(const string& html,string& content)
{
  bool is_content=true;
  for(auto c:html){
    if(is_content){
      //当前已经是正文了
      if(c=='<'){
        //当前遇到了标签
        is_content=false;
      }else{
        //当前是普通字符，就把结果写入到content中
        //需要单独处理下"\n";预期的输出结果是一个行文本文件
        //最终结果是raw_input中每行对应到一个原始的html文档
        //此时就需要把html文档中原来的"\n"都干掉
        if(c=='\n'){
          c=' ';
        }
        content+=c;
      }
    }else{
      //当前已经是标签了
      if(c=='>'){
        //标签结束
        is_content=true;
      }
      //标签里的其他内容直接忽略掉
    }
  }
  return true;
}


bool ParseFile(const string& file_path,DocInfo& doc_info)
{
  //1、先读取文件的内容(一股脑的把整个文件的内容全部读取出来)
  string html;
  bool ret=Common::Util::Read(file_path,html);
  if(!ret){
    cout<<"解析文件失败！读取文件失败！"<<file_path<<endl;
    return false;
  }
  //2、根据文件内容解析出标题(html中有一个title标签就是标题)
  ret=ParseTitle(html,doc_info.title);
  if(!ret){
    cout<<"解析标题失败！"<<endl;
    return false;
  }
  //3、根据文件的路径，构造出对应的在线文档的url
  ret=ParsePath(file_path,doc_info.url);
  if(!ret){
    cout<<"解析路径失败!"<<endl;
    return false;
  }
  //4、根据文件的内容进行去标签,作为doc_info中的content字段的内容
  ret=ParseContent(html,doc_info.content);
  if(!ret){
    cout<<"解析内容失败！"<<endl;
    return false;
  }
  return true;
}


//ofstream类是没有靠背构造函数的(防拷贝的)
//按照参数传参，只能使用引用或者指针
//此处也不能是const引用，否则无法执行里面的写文件操作
void WriteOutput(const DocInfo& doc_info,std::ofstream& output_file)
{
   output_file<<doc_info.title<<"\3"<<doc_info.url<<"\3"<<doc_info.content<<endl;
}



int main()
{
  //1、进行枚举路径
  vector<string> file_list;  //存放枚举出来的结果
  bool ret=EnumFile(g_input_path,file_list);
  if(!ret){
    cout<<"枚举路径失败！"<<endl;
    return 1;
  }
  //2、遍历枚举出来的路径，针对每个文件，单独处理
  std::ofstream output_file(g_output_path.c_str());
  if(!output_file.is_open()){
    cout<<"打开output文件失败"<<endl;
    return 2;
  }
  for(const auto& path:file_list){
    //cout<<path<<endl;
    //创建一个DocInfo对象
    DocInfo doc_info;
    //通过一个函数来负责这里的解析工作
    ret=ParseFile(path,doc_info);
    if(!ret){
      cout<<"解析该文件失败："<<path<<endl;
      continue;
    }
    //3、把解析出来的结果写入到最终的输出文件中
    WriteOutput(doc_info,output_file);
  }
  output_file.close();
  return 0;
}
