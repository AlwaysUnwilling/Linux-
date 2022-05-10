#pragma once 

#include<iostream>
#include<vector>
#include<string>
#include<unordered_map>
#include<unistd.h>
#include"Util.hpp"
#include"Log.hpp"
#include<sstream>
#include<cstdlib>

#define SEP ": "

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
};

class HttpResponse
{
  public:
    std::string status_line;                   //状态行
    std::vector<std::string> response_header;  //响应报头
    std::string blank;                         //空行
    std::string response_body;                 //响应正文
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
    void BuildHttpResponse()
    {}
    void SendHttpResponse()
    {}
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
