#ifndef __RBTREE_HPP__
#define __RBTREE_HPP__

#include<iostream>


namespace my_RBTree
{
    enum Color
    {
        BLACK,
        RED
    };
    template<class K,class V>
    struct RBTreeNode
    {
        struct RBTreeNode<K,V>* _left;
        struct RBTreeNode<K,V>* _right;
        struct RBTreeNode<K,V>* _parent;
        std::pair<K,V> _kv;
        Color _col;
        RBTreeNode(const std::pair<K,V> kv)
        :_left(nullptr),_right(nullptr),_parent(nullptr),_kv(kv),_col(BLACK)
        {}
    };
    template<class K,class V>
    class RBTree
    {
        typedef struct RBTreeNode<K,V> _Node;
    private:
        _Node* _root;
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
        void _Inorder(_Node* root)
        {
            if(root==nullptr){
                return;
            }
            _Inorder(root->_left);
            std::cout<<"Insert DATA: "<<root->_kv.first<<":"<<root->_kv.second<<"::"<<root->_col<<std::endl;
            _Inorder(root->_right);
        }
        _Node* _copyTree(_Node* root)
        {
            if(root==nullptr){
                return nullptr;
            }
            _Node* copyroot=new _Node(root->_kv);
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
        RBTree(const RBTree<K,V>& rbt)
        {
            _root=_copyTree(rbt._root);
        }
        RBTree<K,V>& operator=(RBTree<K,V> rbt)
        {
            if(this!=&rbt){
                std::swap(_root,rbt._root);
            }
            return *this;
        }
        std::pair<_Node*,bool> Insert(const std::pair<K,V>& kv)
        {
            if(_root==nullptr){
                _root=new _Node(kv);
                _root->_col=BLACK;
                return std::make_pair(_root,true);
            }
            _Node* cur=_root;
            _Node* parent=nullptr;
            while(cur){
                if(cur->_kv.first==kv.first){
                    return std::make_pair(cur,false);
                }else if(cur->_kv.first>kv.first){
                    parent=cur;
                    cur=cur->_left;
                }else{
                    parent=cur;
                    cur=cur->_right;
                }
            }
            cur=new _Node(kv);
            cur->_col=RED;
            if(parent->_kv.first>kv.first){
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
            return std::make_pair(newnode,true);
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
