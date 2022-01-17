#include"blockqueue.hpp"



void* Producer_Routine(void* arg)
{
    my_blockqueue::BlockQueue<int>* bq=(my_blockqueue::BlockQueue<int>*)arg;  
    while(1){
        int data=rand()%10+1;
        bq->Push(data);
        std::cout<<"producer push data: "<<data<<std::endl;
    }
}
void* Consumer_Routine(void* arg)
{
    my_blockqueue::BlockQueue<int>* bq=(my_blockqueue::BlockQueue<int>*)arg;  
    while(1){
        int getdata=0;
        bq->Get(getdata);
        std::cout<<"consumer get data: "<<getdata<<std::endl;
        sleep(2);
    }
}
int main()
{
    my_blockqueue::BlockQueue<int> bq;
    pthread_t producer,consumer;
    pthread_create(&producer,nullptr,Producer_Routine,(void*)&bq);
    pthread_create(&consumer,nullptr,Consumer_Routine,(void*)&bq);

    pthread_join(producer,nullptr);
    pthread_join(consumer,nullptr);
    return 0;
}
