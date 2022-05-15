#include<iostream>
#include<cstdlib>
#include<unistd.h>


using namespace std;

int main()
{
  std::string method=getenv("METHOD");
  cerr<<"Test : "<<method<<endl;
  std::string Query_String;
  if("GET"==method){
    Query_String=getenv("QUERY_STRING");
    cerr<<"TEST: "<<Query_String<<endl;
  }else if("POST"==method){
    cerr<<"Content_Length: "<<getenv("CONTENT_LENGTH")<<endl;
    int content_length=atoi(getenv("CONTENT_LENGTH"));
    char ch=0;

    while(content_length--){
      read(0,&ch,1);
      Query_String+=ch;
    }
    cerr<<"TEST: "<<Query_String<<endl;

  }else{

  }
  return 0;
}
