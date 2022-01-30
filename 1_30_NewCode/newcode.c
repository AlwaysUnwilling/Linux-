/*************************************************************************
	> File Name: newcode.c
	> Author: 
	> Mail: 
	> Created Time: Sun 30 Jan 2022 12:35:49 PM CST
    > About:二叉树遍历:描述
编一个程序，读入用户输入的一串先序遍历字符串，根据此字符串建立一个二叉树（以指针方式存储）。 例如如下的先序遍历字符串： ABC##DE#G##F### 其中“#”表示的是空格，空格字符代表空树。建立起此二叉树以后，再对二叉树进行中序遍历，输出遍历结果。
输入描述：
输入包括1行字符串，长度不超过100。
输出描述：
可能有多组测试数据，对于每组数据， 输出将输入字符串建立二叉树后中序遍历的序列，每个字符后面都有一个空格。 每个输出结果占一行。
 ************************************************************************/

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<stdio.h>
#include<unistd.h>

struct TreeNode
{
    char val;
    struct TreeNode* left;
    struct TreeNode* right;
};

void InorderTree(struct TreeNode* root)
{
    if(root==NULL){
        return;
    }
    InorderTree(root->left);
    printf("%c ",root->val);
    InorderTree(root->right);
}
struct TreeNode* BuyTreeNode(char ch)
{
    struct TreeNode* node=(struct TreeNode*)malloc(sizeof(struct TreeNode));
    if(node==NULL){
        exit(-1);
    }
    node->val=ch;
    node->left=NULL;
    node->right=NULL;
    return node;
}
void DestroyTree(struct TreeNode** root)
{
    if(*root==NULL){
        return;
    }
    DestroyTree(&(*root)->left);
    DestroyTree(&(*root)->right);
    free(*root);
    *root=NULL;
}
struct TreeNode* CreateTree(char* buf,ssize_t s,ssize_t* i)
{
    if(buf[*i]=='#'){
        ++(*i);
        return NULL;
    }
    struct TreeNode* root=BuyTreeNode(buf[*i]);
    ++(*i);
    root->left=CreateTree(buf,s,i);
    root->right=CreateTree(buf,s,i);
    return root;
}
void Print(char* buf,ssize_t s)
{
    for(ssize_t i=0;i<s;++i){
        printf("%c ",buf[i]);
    }
    printf("\n");
}
int main()
{
    char buf[1024];
    ssize_t s=read(0,buf,100);
    s-=1;
    buf[s]=0;
    ssize_t i=0;
    struct TreeNode* root=CreateTree(buf,s,&i);
    InorderTree(root);
    printf("\n");
    DestroyTree(&root);
    return 0;
}
