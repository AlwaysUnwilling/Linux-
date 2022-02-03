#include"RBTree.hpp"
#include<time.h>
#include<stdlib.h>



int main()
{
    int a[]={4,2,6,1,3,5,15,7,16,14};
    //int a[] = { 16, 3, 7, 11, 9, 26, 18, 14, 15 };
    //int n=100000;
    my_RBTree::RBTree<int,int> rbt;
    for(auto e:a){
        rbt.Insert(std::make_pair(e,e));
    }
    //srand(time(0));
    /*for(int i=0;i<n;++i){
        int e=rand();
        rbt.Insert(std::make_pair(e,e));
    }*/
    rbt.Inorder();
    std::cout<<rbt.CheckRBTree()<<std::endl;
    /*std::cout<<"rbt1(rbt):"<<std::endl;
    auto rbt1(rbt);
    //rbt1.Inorder();
    my_RBTree::RBTree<int,int> rbt2;
    std::cout<<"rbt2:"<<std::endl;
    int a1[]={16,3,7,11,9,26,18,14,15};
    for(auto e:a1){
        rbt2.Insert(std::make_pair(e,e));
    }
    rbt2.Inorder();
    std::cout<<"rbt2=rbt"<<std::endl;
    rbt2=rbt;
    //rbt2.Inorder();*/
    return 0;
}
