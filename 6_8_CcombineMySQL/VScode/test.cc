#include<iostream>
#include"./include/mysql.h"

using namespace std;

int main()
{
    std::cout<<"hello vscode!"<<std::endl;
    cout<<"mysql client version: "<<mysql_get_client_info()<<endl;
    MYSQL* my=mysql_init(nullptr);
    if(nullptr==mysql_real_connect(my,"39.108.100.112","root","QWer_1234","LgTest",3306,nullptr,0)){
      cerr<<"mysql connect error!"<<endl;
      return 1;
    }
    cout<<"mysql connect success!"<<endl;
    //设置连接编码为utf8
    mysql_set_character_set(my,"utf8");

    //std::string sql="insert into stu values(1004,\'赵六\',1011);";
    //std::string sql="update stu set stu_name='赵六' where stu_id=1004";
    //std::string sql="delete from stu where stu_id=1001";
    //查询所有的数据
    // 1.执行查询语句
    std::string sql="select *from stu";
    if(0!=mysql_query(my,sql.c_str())){
      std::cout<<"execute: "<<sql<<" failed!"<<std::endl;
      return 2;
    }
    std::cout<<"execute: ["<<sql<<"] success"<<std::endl;
    // 2.获取查询结果
    MYSQL_RES* res=mysql_store_result(my);  //需要手动释放res(堆上申请的空间)
    // 3.数据的行列信息
    //获取结果行
    int rows=mysql_num_rows(res);
    //获取列数
    int cols=mysql_num_fields(res);

    //获取所有的列信息
    MYSQL_FIELD* fields=mysql_fetch_field(res);
    for(int i=0;i<cols;++i){
      std::cout<<fields[i].name<<"\t";
    }
    std::cout<<std::endl;


    for(int i=0;i<rows;++i){
      //获取具体的一行
      MYSQL_ROW rowData=mysql_fetch_row(res);
      for(int j=0;j<cols;++j){
        std::cout<<rowData[j]<<"\t\t";
      }
      std::cout<<std::endl;
    }
    free(res);

    mysql_close(my);
    cout<<"close mysql"<<endl;
    return 0;
}
