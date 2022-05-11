#pragma once 

#include<iostream>
#include<sstream>
#include<algorithm>
#include<unordered_map>
#include<vector>
#include<string>
#include<cstdlib>
#include<sys/sendfile.h>
#include<sys/types.h>
#include<unistd.h>
#include<sys/stat.h>
#include<fcntl.h>
#include"Util.hpp"
#include"Log.hpp"


#define HTTP_LINE_END "\r\n"
#define SEP ": "
#define OK 200
#define NOT_FOUND 404
#define WEB_ROOT "wwwroot"
#define HOME_PAGE "index.html"
#define HTTP_VERSION "HTTP/1.0"

static std::string Code2Desc(int code)
{
  std::string desc;
  switch(code)
  {
    case 200:
      desc="OK";
      break;
    case 404:
      desc="NOT FOUND";
      break;
    default:
      break;
  }
  return desc;
}
static std::string Suffix2Desc(const std::string& suffix)
{
  static std::unordered_map<std::string,std::string> suffix2desc={
    {".html","text/html"},
    {".css","text/css"},
    {".js","application/x-javascript"},
    {".jpg","application/x-jpg"},
    {".png","application/x-png"}
  };
  auto iter=suffix2desc.find(suffix);
  if(iter!=suffix2desc.end()){
    return iter->second;
  }else{
    return "text/html";
  }
}
class HttpRequest
{
  public:
    std::string request_line;                //请求行
    std::vector<std::string> request_header; //请求报头
    std::string blank;                       //空行  
    std::string request_body;                //请求正文     
    std::string method;                     //请求方法
    std::string uri;                        //请求资源
    std::string version;                    //客户端版本

    std::unordered_map<std::string,std::string> header_kv;  //请求报头KV
    int content_length=0;
    std::string path;                 //资源
    std::string query_string;         //请求参数
    bool cgi=false;                    //是否需要cgi
    std::string suffix;             //请求资源的后缀
};

class HttpResponse
{
  public:
    std::string status_line;                   //状态行
    std::vector<std::string> response_header;  //响应报头
    std::string blank=HTTP_LINE_END;          //空行
    std::string response_body;                 //响应正文

    int status_code=OK;                          //状态码
    int fd=-1;                             //保存响应body的文件操作句柄
    int size=0;
};

//读取请求，分析请求，构建响应   IO通信

class EndPoint
{
  private:
    int sock;
    HttpRequest http_request;
    HttpResponse http_response;

  private:
    void RcvHttpRequestLine()
    {
      Util::ReadLine(sock,http_request.request_line);
      http_request.request_line.resize(http_request.request_line.size()-1);
    }
    void RcvHttpRequestHeader()
    {
      std::string line;
      while(true){
        line.clear();
        Util::ReadLine(sock,line);
        if(line=="\n"){
          http_request.blank=line;
          break;
        }
        line.resize(line.size()-1);
        http_request.request_header.push_back(line);
      }
    }
    void ParseHttpRequestLine()
    {
      auto& line=http_request.request_line;
      std::stringstream ss(line);
      ss>>http_request.method;
      ss>>http_request.uri;
      ss>>http_request.version;
      //处理method方法。全部转换为大写
      std::transform(http_request.method.begin(),http_request.method.end(),http_request.method.begin(),::toupper);
      //LOG(INFO,http_request.method);
      //LOG(INFO,http_request.uri);
      //LOG(INFO,http_request.version);
    }
    void ParseHttpRequestHeader()
    {
      std::string key;
      std::string value;
      for(auto& iter:http_request.request_header){
        if(Util::CutRequest(iter,key,value,SEP)){
          http_request.header_kv.insert({key,value});
        }
      }
    }
    bool IsNeedRcvHttpRequestBody()
    {
      auto& method=http_request.method;
      if(method=="POST"){
        auto it=http_request.header_kv.find("Content-Length");
        if(it!=http_request.header_kv.end()){
          http_request.content_length=atoi(it->second.c_str());
          return true;
        }
      }
      return false;
    }
    void RcvHttpRequestBody()
    {
      if(IsNeedRcvHttpRequestBody()){
        int content_length=http_request.content_length;
        char ch=0;
        while(content_length){
          ssize_t s=recv(sock,&ch,sizeof(ch),0);
          if(s>0){
            http_request.request_body+=ch;
            content_length--;
          }else{
            break;
          }
        }
      }
    }
    int ProcessCgi()
    {
      std::cout<<"Debug: "<<"Use CGI MODEL "<<std::endl;
      return OK;
    }
    int ProcessNonCgi(int size)
    {
      //构建响应状态行
      http_response.fd=open(http_request.path.c_str(),O_RDONLY);
      if(http_response.fd>=0){
        http_response.status_line=HTTP_VERSION;
        http_response.status_line+=' ';
        http_response.status_line+=std::to_string(http_response.status_code);
        http_response.status_line+=' ';
        http_response.status_line+=Code2Desc(http_response.status_code);
        http_response.status_line+=HTTP_LINE_END;
        http_response.size=size;

        std::string header_line="Content-Length: ";
        header_line+=std::to_string(size);
        header_line+="\r\n";
        http_response.response_header.push_back(header_line);
        header_line="Content-Type: ";
        header_line+=Suffix2Desc(http_request.suffix);
        header_line+="\r\n";
        http_response.response_header.push_back(header_line);
        return OK;
      }

      //添加响应报头
      return 404;
    }
  public:
    EndPoint(int _sock):sock(_sock)
    {}
    void RcvHttpRequest()
    {
      RcvHttpRequestLine();
      RcvHttpRequestHeader();
      ParseHttpRequestLine();
      ParseHttpRequestHeader();
      RcvHttpRequestBody();
    }
    //上传数据到服务器:GET--默认不带参数，但是可以通过URL传参(以?分割)；POST--通过正文传参
    void BuildHttpResponse()
    {
      std::string tmp_path;
      struct stat st;
      int size=0;
      auto& code=http_response.status_code;
      size_t index=0;
      if(http_request.method!="GET" && http_request.method!="POST"){   //请求方法出错
        LOG(WARNING,"METHORD NOT CORRECT");
        code=NOT_FOUND;
        goto END;
      }else if(http_request.method=="GET"){                     //GET请求--拆分请求资源和参数
        size_t pos=http_request.uri.find('?');
        if(pos!=std::string::npos){
          //带参数
          Util::CutRequest(http_request.uri,http_request.path,http_request.query_string,"?");
          http_request.cgi=true;
        }else{
          //不带参数
          http_request.path=http_request.uri;
        }
      }else if(http_request.method=="POST"){
        //POST
        http_request.cgi=true;
      }else{
        //其他方法
        ;
      }
      tmp_path=http_request.path;
      http_request.path=WEB_ROOT;
      http_request.path+=tmp_path;
      //std::cout<<http_request.path<<"------"<<http_request.query_string<<std::endl;
      if(http_request.path[http_request.path.size()-1]=='/'){
        //返回首页
        http_request.path+=HOME_PAGE;
      }
      if(stat(http_request.path.c_str(),&st)==0){
        //请求的资源存在
        //如果请求的是一个可执行程序，那么需要特殊处理
        if(S_ISDIR(st.st_mode)){
          //请求的是一个目录,不被允许的---需要进行相关处理               
          //虽然是一个目录，但是绝对不会以'/'结尾---因为以'/'结尾的情况在上面已经处理了，因此这里处理前应先添加'/'
          http_request.path+='/';
          http_request.path+=HOME_PAGE;
          //修改了http_request.path，需要重新获取stat
          stat(http_request.path.c_str(),&st);  //一定成功
        }
        if((st.st_mode&S_IXUSR)||(st.st_mode&S_IXGRP)||(st.st_mode&S_IXOTH)){
          //所有者、所属组、其他人只要有一个具有可执行权限即可确认求情的是一个可执行文件
          //特殊处理
          http_request.cgi=true;  
        }
        size=st.st_size;
      }else{
        //请求资源不存在
        std::string info=http_request.path;
        info+=" NOT_FOUND!";
        LOG(WARNING,info);
        code=NOT_FOUND;
        goto END;
      }
      
      //到这里说明一切请求都是合法的
      //检测是否需要进行cgi
      //从http_request.path中提取请求资源的类型http_request.suffix;
      index=http_request.path.rfind('.');
      if(index!=std::string::npos){
        http_request.suffix=http_request.path.substr(index);
      }else{
        http_request.suffix=".html";
      }
      if(http_request.cgi){
        code=ProcessCgi();
      }else{
        code=ProcessNonCgi(size);   //不是cgi肯定是GET方法，也一定不带参数，且文件肯定存在---只需要进行静态网页返回即可(需要构建HTTP响应)
      }
END:
    return;
    }
    void SendHttpResponse()
    {
      send(sock,http_response.status_line.c_str(),http_response.status_line.size(),0);
      for(auto& iter:http_response.response_header){
        send(sock,iter.c_str(),iter.size(),0);
      }
      send(sock,http_response.blank.c_str(),http_response.blank.size(),0);
      sendfile(sock,http_response.fd,nullptr,http_response.size);
      close(http_response.fd);
    }
    ~EndPoint()
    {
      close(sock);
    }
};


class Entrance
{
  public:
    static void* HandlerRequest(void* arg)
    {
      LOG(INFO,"HandlerRequest ...begin");
      int sock=*(int*)arg;
      //std::cout<<"get a new link..."<<sock<<std::endl;
      /*std::string out;
      int status=Util::ReadLine(sock,out);
      if(status>0){
        std::cout<<out<<std::endl;
      }
      delete (int*)arg;
      close(sock);*/
      EndPoint* ep=new EndPoint(sock);
      ep->RcvHttpRequest();
      ep->BuildHttpResponse();
      ep->SendHttpResponse();
      delete (int*)arg;
      delete ep;
      LOG(INFO,"HandlerRequest ...end");
      return nullptr;
    }
};
