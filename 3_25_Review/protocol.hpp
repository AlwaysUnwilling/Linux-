#ifndef __PROTOCOL_HPP__
#define __PROTOCOL_HPP__ 

typedef struct request
{
  int x;
  int y;
  char op;
}request_t;

typedef struct response
{
  int code;
  int result;
}response_t;
#endif 
