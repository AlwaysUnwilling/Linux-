#include<iostream>
#include<string>
#include"mysql.h"
#include"comm.hpp"

bool InsertSql(std::string& sql)
{
  //std::cout<<"version: "<<mysql_get_client_info()<<std::endl;
  MYSQL* conn==mysql_init(nullptr);
  mysql_set_character_set(conn,"utf8");
  if(nullptr==mysql_real_connect(conn,"127.0.0.1","http_test","12345678","http_test",3306,nullptr,0)){
    std::cerr<<"MYSQL connect error!"<<std::endl;
    return false;
  }
  std::cout<<"MYSQL connect success!"<<std::endl;

  std::cerr<<"query: "<<sql<<std::endl;
  int ret=mysql_query(conn,sql.c_str());
  std::cerr<<"result: "<<ret<<std::endl;
  mysql_close(conn);
  return true;
}
int main()
{
  std::string query_string;
  if(GetQueryString(query_string)){
    std::string name,passwd;
    CutString(query_string,"&",name,passwd);
    std::string sql_name;
    std::string _name;
    CutString(name,"=",_name,sql_name);

    std::string _passwd;
    std::string sql_passwd;
    CutString(passwd,"=",_passwd,sql_passwd);

    //std::string sql="insert into user (name,passwd) values (\'李四\',\'12345678\')";
    //InsertSql(sql);
    std::string sql="insert into user(name,passwd) values(\'";
    sql+=sql_name;
    sql+="\',\'";
    sql+=sql_passwd;
    sql+="\')";
    if(InsertSql(sql)){
      std::cout<<"<html>";
      std::cout<<"<head><meta charset=\"utf-8\"></head>";
      std::cout<<"<body><h1>注册成功！</h1></body>";
    }
  }
  return 0;
}
