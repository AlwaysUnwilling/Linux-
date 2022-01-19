#include"binarysearchtree.hpp"
#include<string>


//void BSTreeTest1()
//{ 
//    int arr[]={5,3,4,1,7,8,2,6,0,9};
//    BSTree<int> bst;
//    //for(auto e:arr){
//    //    bst.Insert(e);
//    //}
//    //bst.Inorder();
//    //bst.Erase(9);
//    //bst.Inorder();
//    //bst.Insert(9);
//    //bst.Erase(8);
//    //bst.Inorder();
//    //bst.Erase(3);
//    //bst.Inorder();
//
//    //std::cout<<"All clear!"<<std::endl;
//    //for(auto e:arr){
//    //    bst.Erase(e);
//    //    bst.Inorder();
//    //}
//    for(auto e:arr){
//        bst.InsertR(e);
//    }
//    bst.Inorder();
//    bst.EraseR(9);
//    bst.Inorder();
//    bst.InsertR(9);
//    bst.EraseR(8);
//    bst.Inorder();
//    bst.EraseR(3);
//    bst.Inorder();
//
//    std::cout<<"All clear!"<<std::endl;
//    for(auto e:arr){
//        bst.EraseR(e);
//        bst.Inorder();
//    }
//}
//void BSTreeTest2()
//{ 
//    int arr[]={5,3,4,1,7,8,2,6,0,9};
//    BSTree<int> bst;
//    for(auto e:arr){
//        bst.Insert(e);
//    }
//    bst.Inorder();
//    BSTree<int> bst1(bst);
//    bst1.Inorder();
//    BSTree<int> bst2;
//    bst2=bst;
//    bst2.Inorder();
//}
void BSTreeTest3()
{
    BSTree<std::string,std::string> dict;
    dict.InsertR("string","字符串");
    dict.InsertR("hello","你好");
    dict.InsertR("world","世界");
    dict.InsertR("apple","苹果");
    dict.InsertR("banana","香蕉");
    dict.InsertR("melon","西瓜");
    dict.InsertR("learn","学习");
    dict.InsertR("school","学校");
    dict.InsertR("society","社会");
    std::string word;
    while(std::cin>>word){
        auto res=dict.FindR(word);
        if(res!=nullptr){
            std::cout<<word<<"中文意思是："<<res->_val<<std::endl;
        }else{
            std::cout<<"请输入正确的单词！"<<std::endl;
        }
    }

}
void BSTreeTest4()
{
    BSTree<std::string,int> CountArr;
    std::string str[]={"香蕉","梨","橘子","西瓜","葡萄","梨","西瓜","梨","西瓜","橘子","西瓜"};
    int i=0;
    for(;i<11;++i){
        auto res=CountArr.FindR(str[i]);
        if(res){
            res->_val++;
        }else{
            CountArr.InsertR(str[i],1);
        }
    }
    CountArr.Inorder();
}
int main()
{
    //BSTreeTest1();
    //BSTreeTest2();
    //
    //BSTreeTest3();
    BSTreeTest4();
    return 0;
}
