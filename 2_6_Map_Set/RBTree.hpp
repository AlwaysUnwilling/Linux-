#ifndef __RBTREE_HPP__
#define __RBTREE_HPP__

#include<iostream>
#include"ReverseIterator.hpp"


namespace my_RBTree
{
    enum Color
    {
        BLACK,
        RED
    };
    template<class T>
    struct RBTreeNode
    {
        struct RBTreeNode<T>* _left;
        struct RBTreeNode<T>* _right;
        struct RBTreeNode<T>* _parent;
        T _data;
        Color _col;
        RBTreeNode(const T& _data)
        :_left(nullptr),_right(nullptr),_parent(nullptr),_data(_data),_col(BLACK)
        {}
    };
    template<class T,class Ref,class Ptr>
    class __TreeNode_Iterator
    {
        typedef struct RBTreeNode<T> _Node;
        typedef __TreeNode_Iterator<T,Ref,Ptr> Self;
    private:
        _Node* node;
    public:
        typedef Ref reference;
        typedef Ptr pointer;
        __TreeNode_Iterator(_Node* _node)
        :node(_node)
        {}
        Ref operator*()
        {
            return node->_data;
        }
        Ptr operator->()
        {
            return &node->_data;
        }
        Self& operator++()
        {
            if(node->_right){
                _Node* cur=node->_right;
                while(cur->_left){
                    cur=cur->_left;
                }
                node=cur;
            }else{
                _Node* cur=node;
                _Node* parent=node->_parent;
                while(parent && parent->_right==cur){
                    cur=cur->_parent;
                    parent=parent->_parent;
                }
                node=parent;
            }   
            return *this;
        }   
        Self& operator--()
        {
            if(node->_left){
                _Node* cur=node->_left;
                while(cur->_right){
                    cur=cur->_right;
                }
                node=cur;
            }else{
                _Node* cur=node;
                _Node* parent=cur->_parent;
                while(parent && parent->_left==cur){
                    cur=cur->_parent;
                    parent=parent->_parent;
                }
                node=parent;
            }
            return *this;
        }
        bool operator!=(const Self& s)
        {
            return node!=s.node;
        }
        bool operator==(const Self& s)
        {
            return !(node!=s.node);
        }
    };
    template<class K,class T,class Compare>
    class RBTree
    {
        typedef struct RBTreeNode<T> _Node;
    private:
        _Node* _root;
    public:
        typedef __TreeNode_Iterator<T,T&,T*> iterator;
        typedef __TreeNode_Iterator<T,const T&,const T*> const_iterator;
        typedef ReverseIterator<iterator> reverse_iterator;
        reverse_iterator rbegin()
        {
            _Node* cur=_root->_right;
            while(cur && cur->_right){
                cur=cur->_right;
            }
            return reverse_iterator(iterator(cur));
        }
        reverse_iterator rend()
        {
            return reverse_iterator(iterator(nullptr));
        }
        iterator begin() 
        {
            _Node* cur=_root;
            while(cur->_left)
            {
                cur=cur->_left;
            }
            return iterator(cur); 
        }
        const_iterator begin()const  
        {
            _Node* cur=_root;
            while(cur->_left)
            {
                cur=cur->_left;
            }
            return const_iterator(cur);
        }
        iterator end() 
        {
            return iterator(nullptr);
        }
        const_iterator end()const  
        {
            return const_iterator(nullptr);
        }
    private:
        void _clear(_Node*& root)
        {
            if(root==nullptr){
                return ;
            }
            _clear(root->_left);
            _clear(root->_right);
            delete root;
        }
        _Node* _copyTree(_Node* root)
        {
            if(root==nullptr){
                return nullptr;
            }
            _Node* copyroot=new _Node(root->_data);
            copyroot->_col=root->_col;
            copyroot->_left=_copyTree(root->_left);
            copyroot->_right=_copyTree(root->_right);
            return copyroot;
        }
        void RightRotation(_Node* parent)
        {
            _Node* left=parent->_left;
            _Node* rightchild=left->_right;
            _Node* grandfather=parent->_parent;

            parent->_left=rightchild;
            if(rightchild){
                rightchild->_parent=parent;
            }

            left->_right=parent;
            parent->_parent=left;
            
            if(grandfather){
                if(grandfather->_left==parent){
                    grandfather->_left=left;
                }else{
                    grandfather->_right=left;
                }
                left->_parent=grandfather;
            }else{
                _root=left;
                left->_parent=nullptr;
            }
        }
        void LeftRotation(_Node* parent)
        {
            _Node* right=parent->_right;
            _Node* leftchild=right->_left;
            _Node* grandfather=parent->_parent;

            parent->_right=leftchild;
            if(leftchild){
                leftchild->_parent=parent;
            }

            right->_left=parent;
            parent->_parent=right;

            if(grandfather){
                if(grandfather->_left==parent){
                    grandfather->_left=right;
                }else{
                    grandfather->_right=right;
                }
                right->_parent=grandfather;
            }else{
                _root=right;
                right->_parent=nullptr;
            }   
        }
        bool _CheckRBTree(_Node* root,int blackNum,int count)
        {
            if(root==nullptr){
                if(count!=blackNum){
                    std::cout<<"Every by-pass BLACK Node inequality"<<std::endl;
                    return false;
                }
                return true;
            }
            if(root->_col==RED && root->_parent->_col==RED){
                std::cout<<"There are continuous red nodes"<<std::endl;
                return false;
            }
            if(root->_col==BLACK){
                count++;
            }
            return _CheckRBTree(root->_left,blackNum,count)
                && _CheckRBTree(root->_right,blackNum,count);
        }
    public:
        RBTree()
        :_root(nullptr)
        {}
        RBTree(const RBTree<K,T,Compare>& rbt)
        {
            _root=_copyTree(rbt._root);
        }
        RBTree<K,T,Compare>& operator=(RBTree<K,T,Compare> rbt)
        {
            if(this!=&rbt){
                std::swap(_root,rbt._root);
            }
            return *this;
        }
        std::pair<iterator,bool> Insert(const T& data)
        {
            if(_root==nullptr){
                _root=new _Node(data);
                _root->_col=BLACK;
                return std::make_pair(iterator(_root),true);
            }
            _Node* cur=_root;
            _Node* parent=nullptr;
            Compare com;
            while(cur){
                if(com(cur->_data)==com(data)){
                    return std::make_pair(iterator(cur),false);
                }else if(com(cur->_data)>com(data)){
                    parent=cur;
                    cur=cur->_left;
                }else{
                    parent=cur;
                    cur=cur->_right;
                }
            }
            cur=new _Node(data);
            cur->_col=RED;
            if(com(parent->_data)>com(data)){
                parent->_left=cur;
            }else{
                parent->_right=cur;
            }
            cur->_parent=parent;
            _Node* newnode=cur;
            //adjust _col
            while(parent && parent->_col==RED){
                _Node* grandfather=parent->_parent;
                if(grandfather->_left==parent){
                    _Node* uncle=grandfather->_right;
                    if(uncle && uncle->_col==RED){
                        parent->_col=BLACK;
                        uncle->_col=BLACK;
                        grandfather->_col=RED;

                        cur=grandfather;
                        parent=cur->_parent;
                    }else{
                        if(parent->_left==cur){
                            RightRotation(grandfather);
                            parent->_col=BLACK;
                            grandfather->_col=RED;
                        }else{
                            LeftRotation(parent);
                            RightRotation(grandfather);
                            cur->_col=BLACK;
                            grandfather->_col=RED;
                        }
                        break;
                    }
                }else{
                    _Node* uncle=grandfather->_left;
                    if(uncle && uncle->_col==RED){
                        parent->_col=BLACK;
                        uncle->_col=BLACK;
                        grandfather->_col=RED;

                        cur=grandfather;
                        parent=cur->_parent;
                    }else{
                        if(parent->_right==cur){
                            LeftRotation(grandfather);
                            parent->_col=BLACK;
                            grandfather->_col=RED;
                        }else{
                            RightRotation(parent);
                            LeftRotation(grandfather);
                            cur->_col=BLACK;
                            grandfather->_col=RED;
                        }
                        break;
                    }
                }
            }
            _root->_col=BLACK;
            return std::make_pair(iterator(newnode),true);
        }
        iterator Find(const K& key)
        {
            _Node* cur=_root;
            Compare com;
            while(cur){
                if(com(cur->_data)==key){
                    return iterator(cur);
                }else if(com(cur->_data)>key){
                    cur=cur->_left;
                }else{
                    cur=cur->_right;
                }
            }
            return iterator(nullptr);
        }
        void Inorder()
        {
            _Inorder(_root);
        }
        void clear()
        {
            _clear(_root);
        }
        bool CheckRBTree()
        {
            if(_root==nullptr){
                return true;
            }
            if(_root->_col==RED){
                std::cout<<"_root is RED error!"<<std::endl;
                return false;
            }
            _Node* cur=_root;
            int blackNum=0;
            while(cur){
                if(cur->_col==BLACK){
                    blackNum++;
                }
                cur=cur->_left;
            }
            int count=0;
            return _CheckRBTree(_root,blackNum,count);
        }
        ~RBTree()
        {
            if(_root){
                clear();
                _root=nullptr;
            }
        }
    };
}
















#endif
