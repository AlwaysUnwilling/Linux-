#include<iostream>
#include"HttpServer.hpp"
#include<string>
#include<memory>

void Usage(std::string proc)
{
  std::cout<<"Usage:\t\n"<<proc<<" port"<<std::endl;
}
int main(int argc,char* argv[])
{
  if(argc!=2){
    Usage(argv[0]);
    exit(4);
  }
  std::shared_ptr<HttpServer> http_server(new HttpServer(atoi(argv[1])));
  http_server->HttpServerInit();
  http_server->Loop(); 
  return 0;
}
