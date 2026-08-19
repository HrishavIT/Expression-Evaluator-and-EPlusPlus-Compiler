/* Do NOT add/remove any includes statements from this header file */
/* unless EXPLICTLY clarified on Piazza. */
#include "exprtreenode.h"

ExprTreeNode::ExprTreeNode(){
    this->left=NULL;
    this->right=NULL;
}

ExprTreeNode::ExprTreeNode(string t, UnlimitedInt* v){
    type=t;
    val=new UnlimitedRational(v,new UnlimitedInt("1"));
    left=nullptr;
    right=nullptr;
    evaluated_value=new UnlimitedRational();
}

ExprTreeNode::ExprTreeNode(string t, UnlimitedRational* v){
    evaluated_value=new UnlimitedRational();
    type=t;
    val=v;
    left=nullptr;
    right=nullptr;
}

ExprTreeNode::~ExprTreeNode(){
    delete val;
    if(left!=nullptr){
        delete left;
    }
    if(right!=nullptr){
        delete right;
    }
}