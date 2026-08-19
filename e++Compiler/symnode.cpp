/* Do NOT add/remove any includes statements from this header file */
/* unless EXPLICTLY clarified on Piazza. */
#include "symnode.h"
#include<iostream>

//Write your code below this line

SymNode::SymNode(){
    this->height = 0;
    this->address = -1;
    this->key = "";
    this->par = NULL;
    this->left = NULL;
    this->right = NULL;
}

SymNode::SymNode(string k){
    this->key = k;
    this->par = NULL;
    this->left = NULL;
    this->right = NULL;
    this->address = -1;
    this->height = 1;
}

SymNode* SymNode::LeftLeftRotation(){
    return NULL;
}

SymNode* SymNode::RightRightRotation(){
    return NULL;
}

SymNode* SymNode::LeftRightRotation(){
    return NULL;
}

SymNode* SymNode::RightLeftRotation(){
    return NULL;
}

SymNode::~SymNode(){
    delete this;
}

// symnode ka destructor glt h