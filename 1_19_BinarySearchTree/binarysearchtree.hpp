#ifndef __BSTREE_H__
#define __BSTREE_H__

#include<iostream>


template<class K,class V>
struct BSTreeNode
{
    struct BSTreeNode<K,V>* _left;
    struct BSTreeNode<K,V>* _right;
    K _key;
    V _val;
    BSTreeNode(const K& key,const V& val)
    :_key(key)
    ,_val(val)
    ,_left(nullptr)
    ,_right(nullptr)
    {}
};

template<class K,class V>
class BSTree
{
    typedef struct BSTreeNode<K,V> _Node;
private:
    bool _InsertR(_Node*& root,const K& key,const V& val)
    {
        if(root==nullptr){
            root=new _Node(key,val);
            return true;
        }
        if(root->_key>key){
            return _InsertR(root->_left,key,val);
        }else if(root->_key<key){
            return _InsertR(root->_right,key,val);
        }else{
            return false;
        }
    }
    _Node* _FindR(_Node* root,const K& key)
    {
        if(root==nullptr){
            return nullptr;
        }
        if(root->_key>key){
            return _FindR(root->_left,key);
        }else if(root->_key<key){
            return _FindR(root->_right,key);
        }else{
            return root;
        }
    }
    bool _EraseR(_Node*& root,const K& key)
    {
        if(root==nullptr){
            return false;
        }
        if(root->_key>key){
            return _EraseR(root->_left,key);
        }else if(root->_key<key){
            return _EraseR(root->_right,key);
        }else{
            if(root->_left==nullptr){
                _Node* del=root;
                root=root->_right;
                delete del;
            }else if(root->_right==nullptr){
                _Node* del=root;
                root=root->_left;
                delete del;
            }else{
                //_Node* minright=root->_right;
                //_Node* minrightparent=root;
                //while(minright->_left){
                //    minrightparent=minright;
                //    minright=minright->_left;
                //}
                //root->_key=minright->_key;
                //if(minrightparent->_right==minright){
                //    minrightparent->_right=minright->_right;
                //}else{
                //    minrightparent->_left=minright->_right;
                //}
                //delete minright;
                _Node* minright=root->_right;
                while(minright->_left){
                    minright=minright->_left;
                }
                K min=minright->_key;
                _EraseR(root->_right,min);
                root->_key=min;
            }
            return true;
        }  
    }
    void _Destroy(_Node*& root)
    {
        if(root==nullptr){
            return ;
        }
        _Destroy(root->_left);
        _Destroy(root->_right);
        delete root;
    }
    _Node* _CopyNode(_Node* root)
    {
        if(root==nullptr){
            return nullptr;
        }
        _Node* copyNode=new _Node(root->_key,root->_val);
        copyNode->_left=_CopyNode(root->_left);
        copyNode->_right=_CopyNode(root->_right);
        return copyNode;
    }
public:
    BSTree()
    :_root(nullptr)
    {}
    BSTree(const BSTree<K,V>& bst)
    {
        _root=_CopyNode(bst._root);
    }
    BSTree<K,V>& operator=(const BSTree<K,V>& bst)
    {
        if(this!=&bst){
            BSTree<K,V> tmp(bst);
            std::swap(_root,tmp._root);
        }
        return *this;
    }
    //bool Insert(const K& key)
    //{
    //    if(_root==nullptr){
    //        _root=new _Node(key);
    //        return true;
    //    }
    //    _Node* cur=_root;
    //    _Node* parent=nullptr;
    //    while(cur){
    //        if(cur->_key>key){
    //            parent=cur;
    //            cur=cur->_left;
    //        }else if(cur->_key<key){
    //            parent=cur;
    //            cur=cur->_right;
    //        }else{
    //            return false;
    //        }
    //    }
    //    cur=new _Node(key);
    //    if(parent->_key>key){
    //        parent->_left=cur;
    //    }else{
    //        parent->_right=cur;
    //    }
    //    return true;
    //}
    bool InsertR(const K& key,const V& val)
    {
        return _InsertR(_root,key,val);
    }
    void _Inorder(_Node* root)
    {
        if(root==nullptr){
            return;
        }
        _Inorder(root->_left);
        //std::cout<<"Key is:"<<root->_key<<"<==>"<<"Val is:"<<root->_val<<" ";
        std::cout<<root->_key<<":"<<root->_val<<std::endl;
        _Inorder(root->_right);
    }
    void Inorder()
    {
        _Inorder(_root);
        std::cout<<std::endl;
    }
   // _Node* Find(const K& key)
   // {
   //     _Node* cur=_root;
   //     while(cur){
   //         if(cur->_key>key){
   //             cur=cur->_left;
   //         }else if(cur->_key<key){
   //             cur=cur->_right;
   //         }else{
   //             return cur;
   //         }
   //     }
   //     return nullptr;
   // }
    _Node* FindR(const K& key)
    {
        return _FindR(_root,key);
    }
    //bool Erase(const K& key)
    //{
    //    _Node* cur=_root;
    //    _Node* parent=nullptr;
    //    while(cur){
    //        if(cur->_key>key){
    //            parent=cur;
    //            cur=cur->_left;
    //        }else if(cur->_key<key){
    //            parent=cur;
    //            cur=cur->_right;
    //        }else{                     //key exists
    //            //1.Left subtree or right subtree is empty.
    //            if(cur->_left==nullptr){
    //                if(cur==_root){
    //                    _root=cur->_right;
    //                }else{
    //                    if(parent->_left==cur){
    //                        parent->_left=cur->_right;
    //                    }else{
    //                        parent->_right=cur->_right;
    //                    }
    //                }
    //                delete cur;
    //            }else if(cur->_right==nullptr){
    //                if(cur==_root){
    //                    _root=cur->_left;
    //                }else{
    //                    if(parent->_left==cur){
    //                        parent->_left=cur->_left;
    //                    }else{
    //                        parent->_right=cur->_left;
    //                    }
    //                }
    //                delete cur;
    //            }else{              //2.Neither the left subtree nor the right subtree is empty.
    //                _Node* minright=cur->_right;
    //                _Node* minrightparent=cur;
    //                while(minright->_left){
    //                    minrightparent=minright;  
    //                    minright=minright->_left;       
    //                }
    //                cur->_key=minright->_key;
    //                if(minrightparent->_left==minright){
    //                    minrightparent->_left=minright->_right;  
    //                }else{
    //                    minrightparent->_right=minright->_right;
    //                }
    //                delete minright;

    //                //Recursive deletion:先找到cur右节点的最左节点，并保存（K min），然后递归删除min：找到值为min的节点，
    //                //该节点左为空，可以用左为空的删除方法删除该节点。最后将min值赋值给cur->_key.即可完成删除节点值的替换。
    //              //  K min=0;
    //              //  _Node* minright=cur->_right;
    //              //  while(minright->_left){
    //              //      minright=minright->_left;       
    //              //  }
    //              //  this->Erase(min);
    //              //  cur->_key=min;
    //            }
    //            return true;
    //        }
    //    }
    //    return false;
    //}
    bool EraseR(const K& key)
    {
        return _EraseR(_root,key);
    }
    ~BSTree()
    {
        _Destroy(_root);
        _root=nullptr;
    }
private:
    _Node* _root;
};




#endif
