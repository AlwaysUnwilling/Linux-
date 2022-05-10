#pragma once 

#include<iostream>
#include<string>
#include<ctime>

//  [日志级别][时间戳][日志信息][错误文件名称][报错行号]
//  日志级别：INFO:正常的日志信息；
//            WARNING:不影响程序正常执行的警告信息，但是可能会存在风险
//            ERROR:某种错误，虽然出错，但是并不影响程序的执行
//            FATAL:致命信息，一旦发生程序就会被终止，无法执行

#define INFO     1
#define WARNING  2
#define ERROR    3
#define FATAL    4

#define LOG(level,message) Log(#level,__FILE__,__LINE__,message)

void Log(std::string level,std::string file_name,int line,std::string message)
{
  std::cout<<"["<<level<<"]["<<time(nullptr)<<"]["<<file_name<<"]["<<line<<"]["<<message<<"]"<<std::endl;
}
