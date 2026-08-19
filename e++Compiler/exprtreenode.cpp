/* Do NOT add/remove any includes statements from this header file */
/* unless EXPLICTLY clarified on Piazza. */
#include "exprtreenode.h"

//Write your code below this line

ExprTreeNode::ExprTreeNode(){
    this->left=nullptr;
    this->right=nullptr;
}

ExprTreeNode::ExprTreeNode(string t,int v){
    type=t;
    num=v;
    left=nullptr;
    right=nullptr;
}

ExprTreeNode::~ExprTreeNode(){
    if(left!=nullptr){
        delete left;
    }
    if(right!=nullptr){
        delete right;
    }
}

