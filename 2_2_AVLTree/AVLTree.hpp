#ifndef __AVLTREE_HPP__
#define __AVLTREE_HPP__

#include<iostream>
#include<assert.h>

namespace my_AVLTree
{
    template<class K,class V>
    struct AVLTreeNode
    {
        AVLTreeNode<K,V>* _left;
        AVLTreeNode<K,V>* _right;
        AVLTreeNode<K,V>* _parent;
        std::pair<K,V> _kv;
        int _bf;
        AVLTreeNode(std::pair<K,V> kv)
        :_left(nullptr),_right(nullptr),_parent(nullptr),_bf(0),_kv(kv)
        {}
    };

    template<class K,class V>
    class AVLTree
    {
        typedef struct AVLTreeNode<K,V> _Node;
    private:
        _Node* _root;
    private:
        void _Inorder(_Node* root)
        {
            if(root==nullptr){
                return;
            }
            _Inorder(root->_left);
            std::cout<<root->_kv.first<<":"<<root->_kv.second<<" # balance factor:"<<root->_bf<<std::endl;
            _Inorder(root->_right);
        }
        void RightRotation(_Node* parent)
        {
            _Node* grandParent=parent->_parent;
            _Node* left=parent->_left;
            _Node* rightChild=left->_right;

            parent->_left=rightChild;
            if(rightChild){
                rightChild->_parent=parent;
            }

            if(grandParent){
                if(grandParent->_left==parent){
                    grandParent->_left=left;
                }else{
                    grandParent->_right=left;
                }
                left->_parent=grandParent;
            }else{
                _root=left;
                _root->_parent=nullptr;
            }

            left->_right=parent;
            parent->_parent=left;

            parent->_bf=left->_bf=0;    
        }
        void LeftRotation(_Node* parent)
        {
            _Node* grandParent=parent->_parent;
            _Node* right=parent->_right;
            _Node* leftChild=right->_left;

            parent->_right=leftChild;
            if(leftChild){    
                leftChild->_parent=parent;
            }

            if(grandParent){
                if(grandParent->_left==parent){
                    grandParent->_left=right;
                }else{
                    grandParent->_right=right;
                }
                right->_parent=grandParent;
            }else{
                _root=right;
                _root->_parent=nullptr;
            }

            right->_left=parent;
            parent->_parent=right;

            parent->_bf=right->_bf=0;
        }
        void RightLeftrotation(_Node* parent)
        {
            _Node* right=parent->_right;
            _Node* leftChild=right->_left;
            if(leftChild==nullptr){

            }
            int bf=leftChild->_bf;

            RightRotation(parent->_right);
            LeftRotation(parent);

            if(bf==-1){
                right->_bf=1;
                leftChild->_bf=0;
                parent->_bf=0;
            }else if(bf==1){
                right->_bf=0;
                leftChild->_bf=0;
                parent->_bf=-1;
            }else if(bf==0){
                right->_bf=0;
                leftChild->_bf=0;
                parent->_bf=0;
            }else{
                std::cout<<"balance factor(_bf) error!"<<std::endl;
                assert(false);
            }
        }
        void LeftRightrotation(_Node* parent)
        {
            _Node* left=parent->_left;
            _Node* rightChild=left->_right;
            int bf=rightChild->_bf;
            
            LeftRotation(parent->_left);
            RightRotation(parent);

            if(bf==-1){
                left->_bf=0;
                rightChild->_bf=0;
                parent->_bf=1;
            }else if(bf==1){
                left->_bf=-1;
                rightChild->_bf=0;
                parent->_bf=0;
            }else if(bf==0){
                left->_bf=0;
                rightChild->_bf=0;
                parent->_bf=0;
            }else{
                std::cout<<"balance factor(_bf) error!"<<std::endl;
                assert(false);
            }
        }
        int TreeHeight(_Node* root)
        {
            if(root==nullptr){
                return 0;
            }
            int leftHeight=TreeHeight(root->_left);
            int rightHeight=TreeHeight(root->_right);
            return leftHeight>rightHeight?leftHeight+1:rightHeight+1;
        }
        bool _IsBalanceTree(_Node* root)
        {
            if(root==nullptr){
                return true;
            }
            int leftHeight=TreeHeight(root->_left);
            int rightHeight=TreeHeight(root->_right);
            if(rightHeight-leftHeight!=root->_bf){
                std::cout<<"balance factor error!: "<<root->_kv.first<<std::endl;
                return false;
            }
            return abs(leftHeight-rightHeight)<2
                && _IsBalanceTree(root->_left)
                && _IsBalanceTree(root->_right);
        }
        _Node* _CopyTree(_Node* root)
        {
            if(root==nullptr){
                return nullptr;
            }
            _Node* copyroot=new _Node(root->_kv);
            copyroot->_bf=root->_bf;
            copyroot->_left=_CopyTree(root->_left);
            copyroot->_right=_CopyTree(root->_right);
            return copyroot;
        }
        void _clear(_Node*& root)
        {
            if(root==nullptr){
                return ;
            }
            _clear(root->_left);
            _clear(root->_right);
            delete root;
        }
    public:
        AVLTree(const std::pair<K,V>& kv)
        :_root(kv)
        {}
        AVLTree()
        :_root(nullptr)
        {}
        AVLTree(const AVLTree<K,V>& avt)
        {
            if(avt._root==nullptr){
                _root=nullptr;
            }else{    
                _root=_CopyTree(avt._root);
            }
        }
        AVLTree<K,V>& operator=(AVLTree<K,V> avt)
        {
            
            if(this!=&avt){
                std::swap(_root,avt._root);
            }
            return *this;
        }
        void Inorder()
        {
            _Inorder(_root);
        }
        bool Insert(const std::pair<K,V>& kv)
        {
            if(_root==nullptr){
                _root=new _Node(kv);
                return true;
            }
            _Node* cur=_root;
            _Node* parent=nullptr;
            while(cur){
                if(cur->_kv.first==kv.first){
                    return false;
                }else if(cur->_kv.first>kv.first){
                    parent=cur;
                    cur=cur->_left;
                }else{
                    parent=cur;
                    cur=cur->_right;
                }
            }
            cur=new _Node(kv);
            if(parent->_kv.first>kv.first){
                parent->_left=cur;
                cur->_parent=parent;
            }else{
                parent->_right=cur;
                cur->_parent=parent;
            }
            //adjust _bf;_bf=height_right-height_left;            
            while(cur!=_root){
                if(parent->_left==cur){
                    parent->_bf--;
                }else{
                    parent->_bf++;
                }
                if(parent->_bf==0){
                    break;
                }else if(parent->_bf==1 || parent->_bf==-1){
                    cur=parent;
                    parent=parent->_parent;
                }else if(parent->_bf==2 || parent->_bf==-2){
                    //Four kinds of rotation
                    //RightRotation
                    if(parent->_bf==-2 && cur->_bf==-1){
                        RightRotation(parent);
                    }else if(parent->_bf==-2 && cur->_bf==1){
                        LeftRightrotation(parent);
                    }else if(parent->_bf==2 && cur->_bf==1){
                        LeftRotation(parent);
                    }else if(parent->_bf==2 && cur->_bf==-1){
                        RightLeftrotation(parent);
                    }else{
                        std::cout<<"balance factor(_bf) error!"<<std::endl;
                        exit(-1);
                    }
                    break;
                }else{
                    std::cout<<"parent _bf error!"<<std::endl;
                    assert(false);
                }
            }
            return true;
        }
        _Node* Find(const K& key)
        {
            _Node* cur=_root;
            while(cur){
                if(cur->_kv.first==key){
                    return cur;
                }else if(cur->_kv.first>key){
                    cur=cur->_left;
                }else{
                    cur=cur->_right;
                }
            }
            return nullptr;
        }
        bool IsAVLTree()
        {
            return _IsBalanceTree(_root);
        }
        void clear()
        {
            _clear(_root);
        }
        ~AVLTree()
        {
            if(_root){    
                clear();
            }
        }
    };
}








#endif
