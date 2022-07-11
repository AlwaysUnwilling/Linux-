#include<iostream>
#include<vector>
#include<string>
#include<unordered_map>
#include"../searcher/searcher.h"
#include"cpp-httplib/httplib.h"

using std::string;
using std::vector;
using std::unordered_map;
using std::cin;
using std::cout;
using std::endl;

int main()
{
  using namespace httplib;
  //1、创建searcher对象
  Searcher::searcher scher; 
  bool ret=scher.Init("../data/tmp/raw_input");
  if(!ret){
    cout<<"Searcher 初始化失败"<<endl;
    return 1;
  }
  //2、创建server对象
  /*Server server;
  server.Get("/searcher",[](const Request& req,Response& resp){
      (void) req;
      resp.set_content("hello","text/html");
      });
  //启动服务器
  server.listen("0.0.0.0",8080);*/
  Server server;
  server.Get("/searcher",[&scher](const Request& req,Response& resp){
      if(!req.has_param("query")){
        resp.set_content("请检查您的查询是否正确","text/plain; charset=utf-8");
      }
      string query=req.get_param_value("query");
      string results;
      scher.searchObj(query,results);
      //resp.set_content("hello","text/html");
      resp.set_content(results,"application/json; charset=utf-8");
      cout<<query<<endl;
      });
  //告诉服务器，静态资源存放在wwwroot目录下(html,css,js,图片...)
  //服务器启动之后，就可以通过http://127.0.0.1:10001/index.html来访问到该页面了
  server.set_base_dir("./wwwroot");
  //3、启动服务器
  server.listen("0.0.0.0",8080);
  return 0;
}
