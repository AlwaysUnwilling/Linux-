#include"BlockQueue.hpp"
#include"Task.hpp"
#include<memory>
#include<cstdlib>

void* ConsumerRoutine(void* arg)
{
    std::shared_ptr<my_BlcokQueue::BlockQueue<Task>> bq=*(std::shared_ptr<my_BlcokQueue::BlockQueue<Task>>*)arg;
    while(true){
        Task task;
        bq->Pop(task);
        std::cout<<"Consumer doing Task: "<<std::endl;
        task.Run();
        sleep(1);
    }
}
void* ProductorRoutine(void* arg)
{
    std::shared_ptr<my_BlcokQueue::BlockQueue<Task>> bq=*(std::shared_ptr<my_BlcokQueue::BlockQueue<Task>>*)arg;
    const char* OP="+-*/%";
    while(true){
        int x=rand()%100;
        int y=rand()%50;
        char op=*(OP + rand()%5);
        Task task(x,y,op);
        bq->Push(task);
        std::cout<<"Productor pushing Task: "<<std::endl;
        sleep(1);
    }
}
void TestProducorConsumerModel()
{
    my_BlcokQueue::BlockQueue<int>* bq=new my_BlcokQueue::BlockQueue<int>;
    bq->BlockQueueInit();
    std::shared_ptr<my_BlcokQueue::BlockQueue<int>> sp(bq); 
    auto sp1=sp;
    pthread_t c,p;
    pthread_create(&c,nullptr,ConsumerRoutine,(void*)&sp);
    pthread_create(&p,nullptr,ProductorRoutine,(void*)&sp1);

    // pthread_t c,p;
    // pthread_create(&c,nullptr,ConsumerRoutine,(void*)bq);
    // pthread_create(&p,nullptr,ProductorRoutine,(void*)bq);

    pthread_join(c,nullptr);
    pthread_join(p,nullptr);
}
int main()
{
    TestProducorConsumerModel();
    return 0;
}