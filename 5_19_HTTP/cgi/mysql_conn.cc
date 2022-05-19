#include<iostream>
#include"mysql.h"

int main()
{
  std::cout<<"version: "<<mysql_get_client_info()<<std::endl;
  return 0;
}
