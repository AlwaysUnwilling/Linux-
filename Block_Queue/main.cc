#include"blockqueue.hpp"

using namespace std;


void* customer_run(void* arg)
{
    BlcokQueue* bq=(BlcokQueue*)arg; 
    while(true){
        int n=0;
        bq->Get(n);
        cout<<"Customer Data Is:"<<n<<endl;
    }
}
void* productor_run(void* arg)
{
    BlcokQueue* bq=(BlcokQueue*)arg; 
    while(true){
        sleep(2);
        int data=rand()%10+1;
        bq->Put(data);
        cout<<"Productor Data Is:"<<data<<endl;
    }
}
int main()
{
    BlcokQueue* bq=new BlcokQueue(5);
    pthread_t cus,pro;
    pthread_create(&cus,nullptr,customer_run,(void*)bq);
    pthread_create(&pro,nullptr,productor_run,(void*)bq);

    pthread_join(cus,nullptr);
    pthread_join(pro,nullptr);
    delete bq;
    return 0;
}
