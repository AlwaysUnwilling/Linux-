#include"AVLTree.hpp"


int main()
{
    my_AVLTree::AVLTree<int,int> avt;
    avt.Insert(std::pair<int,int>(10,10));
    avt.Insert(std::pair<int,int>(7,7));
    avt.Insert(std::pair<int,int>(12,12));
    avt.Insert(std::pair<int,int>(8,8));
    avt.Insert(std::pair<int,int>(15,15));
    avt.Insert(std::pair<int,int>(1,1));
    avt.Insert(std::pair<int,int>(2,2));
    avt.Insert(std::pair<int,int>(3,3));
    avt.Insert(std::pair<int,int>(0,0));
    avt.Insert(std::pair<int,int>(9,9));
    avt.Inorder();
    std::cout<<std::endl;
    avt.Insert(std::pair<int,int>(-1,-1));
    avt.Insert(std::pair<int,int>(4,4));
    avt.Insert(std::pair<int,int>(5,5));
    avt.Insert(std::pair<int,int>(6,6));
    avt.Inorder();
    std::cout<<avt.IsAVLTree()<<std::endl;

    std::cout<<std::endl;
    my_AVLTree::AVLTree<int,int> avt1(avt);
    avt.Inorder();
    std::cout<<std::endl;

    my_AVLTree::AVLTree<int,int> avt2;
    avt2.Insert(std::pair<int,int>(99,99));
    avt2.Insert(std::pair<int,int>(9,9));
    avt2.Insert(std::pair<int,int>(199,199));
    avt2.Insert(std::pair<int,int>(17,17));
    avt2.Insert(std::pair<int,int>(18,18));
    avt2.Inorder();

    avt2=avt;
    std::cout<<&avt2<<" #### "<<&avt<<std::endl;
    avt2.Inorder();
    std::cout<<avt.IsAVLTree()<<std::endl;
    return 0;
}
