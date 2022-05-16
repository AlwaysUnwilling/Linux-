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
#include<sys/wait.h>
#include<unistd.h>
#include<sys/stat.h>
#include<fcntl.h>
#include"Util.hpp"
#include"Log.hpp"


#define HTTP_LINE_END "\r\n"
#define SEP ": "
#define WEB_ROOT "wwwroot"
#define HOME_PAGE "index.html"
#define HTTP_VERSION "HTTP/1.0"
#define PAGE_404 "404.html"

#define OK 200
#define NOT_FOUND 404
#define BAD_REQUEST 400
#define SERVER_ERROR 500

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
    int size=0;
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
          LOG(INFO,"POST Method,Content-Length "+it->second);
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
        LOG(INFO,http_request.request_body);
      }
    }
    int ProcessCgi()
    {
      //std::cout<<"Debug: "<<"Use CGI MODEL "<<std::endl;
      //新线程，但是从头到尾只有一个进程就是httpserver
      //因此进行程序替换时不能直接替换，需要创建子进程，让子进程去替换
      //而且我们需要父子进程间进行通信--父进程需要把数据传给子进程，而子进程需要把结果返回给父进程
      //父子进程间的通信首选--pipe(自动维护了通信的同步与互斥，但是我们需要进行父子进程的双向
      //通信，因此需要俩个管道来保证)
      int input[2];               //以父进程角度创建俩个管道--输入&&输出
      int output[2];
      int code=OK;
      if(pipe(input)<0){
        LOG(ERROR,"pipe input error!");
        code=SERVER_ERROR;
        return code;
      }
      if(pipe(output)<0){
        LOG(ERROR,"pipe output error!");
        code=SERVER_ERROR;
        return code;
      }
      auto& bin=http_request.path;
      auto& query_string=http_request.query_string; //GET
      auto& body=http_request.request_body;        //POST
      std::string query_string_env;
      std::string method_string_env;
      std::string content_length_env;
      pid_t pid=fork();
      if(pid==0){
        close(input[1]);//关闭写端，保留读端
        close(output[0]); //关闭读端，保留写端
        method_string_env="METHOD=";
        method_string_env+=http_request.method;
        putenv((char*)method_string_env.c_str());
        if(http_request.method=="GET"){
          query_string_env="QUERY_STRING=";
          query_string_env+=query_string;
          LOG(INFO,"PUTENV: "+query_string);
          putenv((char*)query_string_env.c_str());
        }else if(http_request.method=="POST"){
          content_length_env="CONTENT_LENGTH=";
          content_length_env+=std::to_string(http_request.content_length);
          putenv((char*)content_length_env.c_str());
        }else{
          //Do nothing
        }
        //exec*
        //子进程程序替换只替换代码和数据，并不替换内核进程相关的数据结构，包括：文件描述符表
        //即：子进程发成程序替换后，父进程打开的文件，替换后的子进程也是被打开的，只是
        //子进程找不到了对应的文件描述符
        //因此我们通过重定向让子进程向0号文件描述符读，1号文件描述符写来实现父子进程的通信
        //重定向必须在子进程发生程序替换前进行重定向！！！！
        dup2(input[0],0);
        dup2(output[1],1);
        //重定向完成后，目标子进程对应的读写文件描述符是多少并不需要知道，
        //只需要从0中读取，向1中写入即可
        execl(bin.c_str(),bin.c_str(),nullptr);
        exit(1);
      }else if(pid<0){
        LOG(ERROR,"fork error!");
        return SERVER_ERROR;
      }else{
        //parent 
        close(input[0]);
        close(output[1]);
        if(http_request.cgi){
          const char* start=body.c_str();
          int total=0;
          int size=0;
          while(total<http_request.content_length 
              && (size=write(input[1],start+total,body.size()-total))>0){
            total+=size;
          }
          char ch=0;
          while(read(output[0],&ch,1)>0){
            //不能直接send(sock)
            //因为这里父进程读到的结果是CGI程序返回的响应正文部分。而应该添加到http_response.body中
            http_response.response_body+=ch;
          }
        }
        //对于GET方法如何把数据传给子进程，可以采用POST的方法的方式来串，但是
        //由于通常GET方法的参数比较短小，通过读写反而会降低效率，一般会通过环境变量来传递
        //环境变量：1、具有全局属性，可以被子进程继承下去的；2、不受exec*系列程序替换函数的影响
        
        int status=0;
        pid_t ret=waitpid(pid,&status,0);
        if(pid==ret){
          if(WIFEXITED(status)){
            if(WEXITSTATUS(status)==0){
              code=OK;
            }else{
              code=BAD_REQUEST;
            } 
          }else{
            code=SERVER_ERROR;
          }
        }

        close(input[1]);
        close(output[0]);
      }
      return code;
    }
    int ProcessNonCgi()
    {
      //构建响应状态行
      http_response.fd=open(http_request.path.c_str(),O_RDONLY);
      if(http_response.fd>=0){

        /*http_response.status_line=HTTP_VERSION;
        http_response.status_line+=' ';
        http_response.status_line+=std::to_string(http_response.status_code);
        http_response.status_line+=' ';
        http_response.status_line+=Code2Desc(http_response.status_code);
        http_response.status_line+=HTTP_LINE_END;

        std::string header_line="Content-Length: ";
        header_line+=std::to_string(http_response.size);
        header_line+="\r\n";
        http_response.response_header.push_back(header_line);
        header_line="Content-Type: ";
        header_line+=Suffix2Desc(http_request.suffix);
        header_line+="\r\n";
        http_response.response_header.push_back(header_line);*/ 

        LOG(INFO,"Open http_request.fd success");
        return OK;
      }

      //添加响应报头
      return NOT_FOUND;
    }
    void BuildOKHttpResponse()
    {
      std::string line="Content-Type: ";
      line+=Suffix2Desc(http_request.suffix);
      line+=HTTP_LINE_END;
      http_response.response_header.push_back(line);
      line="Content-Length: ";
      if(!http_request.cgi){
        line+=std::to_string(http_request.size);   //GET
      }else{
        line+=std::to_string(http_response.response_body.size());   //POST
      }
      line+=HTTP_LINE_END;
      http_response.response_header.push_back(line);

    }
    void HandlerNotError(std::string page)
    {
      //返回404页面
      //如果在cgi执行程序中出错，那么本来应该返回出错页面，但是我们这里是通过http_request.cgi 
      //来判断返回页面的，始终是返回的正确页面，所以只要进入到这个函数中，就将cgi设置为false
      http_request.cgi=false;
      http_response.fd=open(page.c_str(),O_RDONLY);
      if(http_response.fd>0){
        struct stat st;
        stat(page.c_str(),&st);   //获取文件属性
        std::string line="Content-Type: text/html";
        line+=HTTP_LINE_END;
        http_response.response_header.push_back(line);
        line="Content-Length: ";
        line+=std::to_string(st.st_size);
        line+=HTTP_LINE_END;
        http_response.response_header.push_back(line);
        http_request.size=st.st_size;
      }      
    }
    void BuildHttpResponseHelper()
    {
      auto& code=http_response.status_code;

      //构建状态行
      auto& status_line=http_response.status_line;
      status_line+=HTTP_VERSION;
      status_line+=" ";
      status_line+=std::to_string(code);
      status_line+=" ";
      status_line+=Code2Desc(code);
      status_line+=HTTP_LINE_END;

      //构建响应正文，可能包含响应报头
      std::string page=WEB_ROOT;
      page+="/";
      switch(code){
        case OK:
          BuildOKHttpResponse();
          break;
        case NOT_FOUND:
          page+=PAGE_404;
          HandlerNotError(page);
          break;
        case SERVER_ERROR:
          page+=PAGE_404;
          HandlerNotError(page);
          break;
        case BAD_REQUEST:
          page+=PAGE_404;
          HandlerNotError(page);
          break;
        default:
          break;
      }
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
      auto& code=http_response.status_code;
      size_t index=0;
      if(http_request.method!="GET" && http_request.method!="POST"){   //请求方法出错
        LOG(WARNING,"METHORD NOT CORRECT");
        code=BAD_REQUEST;
        goto END;
      }else if(http_request.method=="GET"){                     //GET请求--拆分请求资源和参数
        size_t pos=http_request.uri.find('?');
        if(pos!=std::string::npos){
          //带参数
          Util::CutRequest(http_request.uri,http_request.path,http_request.query_string,"?");
          LOG(INFO,"http_request.query_string: "+http_request.query_string);
          http_request.cgi=true;
        }else{
          //不带参数
          http_request.path=http_request.uri;
        }
      }else if(http_request.method=="POST"){
        //POST
        http_request.cgi=true;
        http_request.path=http_request.uri;
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
        http_request.size=st.st_size;
      }else{
        //请求资源不存在
        std::string info=http_request.path;
        info+=" NOT_FOUND!";
        LOG(WARNING,http_request.path+" NOT_FOUND");
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
        code=ProcessNonCgi();   //不是cgi肯定是GET方法，也一定不带参数，且文件肯定存在---只需要进行静态网页返回即可(需要构建HTTP响应)
      }
END:
      BuildHttpResponseHelper();
    }
    void SendHttpResponse()
    {
      send(sock,http_response.status_line.c_str(),http_response.status_line.size(),0);
      for(auto& iter:http_response.response_header){
        send(sock,iter.c_str(),iter.size(),0);
      }
      send(sock,http_response.blank.c_str(),http_response.blank.size(),0);
      if(http_request.cgi){
        auto& response_body=http_response.response_body;
        LOG(INFO,"BODY: "+response_body);
        int size=0;
        size_t total=0;
        const char* start=response_body.c_str();
        while(total<response_body.size() 
            && (size=send(sock,start+total,response_body.size()-total,0))>0){
          LOG(INFO,"send sucess: "+std::to_string(size));
          total+=size;
        }
      }else{
        sendfile(sock,http_response.fd,nullptr,http_request.size);
      }
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
