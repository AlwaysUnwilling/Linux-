#include"searcher.h"

void TestIndex()
{
  Searcher::Index index;
  bool ret=index.Build("../data/tmp/raw_input");
  if(!ret){
    std::cout<<"索引构造失败！"<<std::endl;
    return ;
  }
  auto* invertedlist=index.GetInvertedList("filesystem");
  for(const auto& weight:*invertedlist){
    std::cout<<"doc_id:"<<weight.doc_id<<" weight:"<<weight.weight<<std::endl;
    auto* doc_info=index.GetDocInfo(weight.doc_id);
    std::cout<<"title:"<<doc_info->title<<std::endl;
    std::cout<<"url:"<<doc_info->url<<std::endl;
    std::cout<<"content:"<<doc_info->content<<std::endl;
    std::cout<<"==============================================="<<std::endl;
  }

}
void TestSearcher()
{
  Searcher::searcher scher;
  bool ret=scher.Init("../data/tmp/raw_input");
  if(!ret){
    std::cout<<"scher初始化失败"<<std::endl;
    return ;
  }
  while(true){
    std::cout<<"Searcher:"<<std::flush;
    string query;
    std::cin>>query;
    if(!std::cin.good()){
      //读到EOF
      std::cout<<"goodbye"<<std::endl;
      break;
    }
    string results;
    scher.searchObj(query,results);
    std::cout<<results<<std::endl;
    std::cout<<"***********************************************************"<<std::endl;
  }
}
int main()
{
  //TestIndex();
  TestSearcher();
  return 0;
}
