// UnlimitedInt *UnlimitedInt::add(UnlimitedInt *i1, UnlimitedInt *i2)
// {
//     if (i1->get_sign() == i2->get_sign())
//     {
//         int i_1 = i1->get_size();
//         int i_2 = i2->get_size();
//         UnlimitedInt *result = new UnlimitedInt();
//         result->sign = i1->sign;
//         int max_size = max(i_1, i_2);

//         result->capacity = max_size + 2;
//         result->unlimited_int = new int[result->capacity];
//         int carry = 0;
//         for (int i = 1; i <= max_size; i++)
//         {
//             int i_11 = 0;
//             if (i <= i_1)
//             {
//                 i_11 = i1->unlimited_int[i];
//             }

//             int i_22 = 0;
//             if (i <= i_2)
//             {
//                 i_22 = i2->unlimited_int[i];
//             }

//             int sum = i_11 + i_22 + carry;
//             int input = sum % 10;
//             carry = sum / 10;
//             result->unlimited_int[i] = input;
//         }
//         if (carry != 0)
//         {
//             result->size = max_size + 1;
//             result->unlimited_int[max_size + 1] = carry;
//         }
//         else
//         {
//             result->size = max_size;
//         }
//         if (result->get_sign() == -1)
//         {
//             result->unlimited_int[0] = -1;
//             result->sign = -1;
//         }
//         return result;
//     }
//     else
//     {
//         if (i1->get_sign() == 1)
//         {
//             UnlimitedInt *temp = i2;
//             temp->unlimited_int[0] = 1;
//             temp->sign = 1;
//             return sub(i1, temp);
//         }

//         else
//         {
//             UnlimitedInt *temp = i1;
//             temp->unlimited_int[0] = 1;
//             temp->sign = 1;
//             return sub(i2, temp);
//         }
//     }
// }

// UnlimitedInt *UnlimitedInt::sub(UnlimitedInt *i1, UnlimitedInt *i2)
// {
//     if (i1 == i2)
//     {
//         UnlimitedInt *result = new UnlimitedInt("0");
//         return result;
//     }
//     if (i1->get_sign() == i2->get_sign())
//     {
//         if (i1->get_sign() == 1)
//         {
//             UnlimitedInt *result = new UnlimitedInt();
//             UnlimitedInt *larger = compare(i1, i2);
//             if (larger == i1)
//             {
//                 int max_size = larger->get_size();
//                 result->capacity = max_size + 2;
//                 result->sign = 1;
//                 result->unlimited_int = new int[result->capacity];
//                 int borrow = 0;
//                 for (int i = 1; i <= max_size; i++)
//                 {
//                     int i_11 = 0;
//                     if (i <= i1->get_size())
//                     {
//                         i_11 = i1->unlimited_int[i];
//                     }

//                     int i_22 = 0;
//                     if (i <= i2->get_size())
//                     {
//                         i_22 = i2->unlimited_int[i];
//                     }

//                     int diff = i_11 - i_22 - borrow;

//                     if (diff < 0)
//                     {
//                         diff += 10;
//                         borrow = 1;
//                     }
//                     else
//                     {
//                         borrow = 0;
//                     }
//                     result->unlimited_int[i] = diff;
//                 }
//                 while (max_size > 0 && result->unlimited_int[max_size] == 0)
//                 {
//                     max_size--;
//                 }
//                 result->size = max_size;
//                 result->unlimited_int[0] = 1;
//                 return result;
//             }
//             else
//             {
//                 int max_size = larger->get_size();
//                 result->capacity = max_size + 2;
//                 result->sign = -1;
//                 result->unlimited_int = new int[result->capacity];
//                 int borrow = 0;
//                 for (int i = 1; i <= max_size; i++)
//                 {
//                     int i_11 = 0;
//                     if (i <= i1->get_size())
//                     {
//                         i_11 = i1->unlimited_int[i];
//                     }

//                     int i_22 = 0;
//                     if (i <= i2->get_size())
//                     {
//                         i_22 = i2->unlimited_int[i];
//                     }

//                     int diff = i_22 - i_11 - borrow;

//                     if (diff < 0)
//                     {
//                         diff += 10;
//                         borrow = 1;
//                     }
//                     else
//                     {
//                         borrow = 0;
//                     }
//                     result->unlimited_int[i] = diff;
//                 }
//                 while (max_size > 0 && result->unlimited_int[max_size] == 0)
//                 {
//                     max_size--;
//                 }
//                 result->size = max_size;
//                 result->unlimited_int[0] = -1;
//                 return result;
//             }
//         }
//         else
//         {
//             UnlimitedInt *temp = i2;
//             temp->sign = 1;
//             temp->unlimited_int[0] = 1;
//             UnlimitedInt *temp2 = i1;
//             temp2->sign = 1;
//             temp2->unlimited_int[0] = 1;
//             return sub(temp, temp2);
//         }
//     }
//     else
//     {
//         if (i1->get_sign() == -1)
//         {
//             UnlimitedInt *temp = i2;
//             temp->sign = -1;
//             temp->unlimited_int[0] = -1;
//             return add(i1, i2);
//         }
//         else
//         {
//             UnlimitedInt *temp = i2;
//             temp->sign = 1;
//             temp->unlimited_int[0] = 1;
//             return add(i1, i2);
//         }
//     }
// }



// UnlimitedInt *UnlimitedInt ::mul(UnlimitedInt *i1, UnlimitedInt *i2)
// {
//     UnlimitedInt *i = new UnlimitedInt();
//     i->capacity = (i1->size * i2->size) + 1;
//     i->size = (i1->size * i2->size);
//     i->sign = i1->sign * i2->sign;
//     i->unlimited_int = new int[i->capacity];
//     i->unlimited_int[0] = i->sign;
//     int carry = 0;
//     for(int a = 1; a<=i->size; a++){
//         i->unlimited_int[a] = 0;
//     }
//     for(int j = i2->size; j>=1; j--){
//         UnlimitedInt* copy = new UnlimitedInt(i->to_string() + "0");
//         delete i;
//         i = copy;
//         UnlimitedInt* dummy = new UnlimitedInt();
//         dummy->sign = i->sign;
//         dummy->capacity = i1->size + 1;
//         dummy->size = i1->size + 1;
//         dummy->unlimited_int = new int[dummy->capacity];
//         dummy->unlimited_int[0] = i->sign;
//         for(int k = 1; k<=i1->size; k++){
//             dummy->unlimited_int[j+k-1] = ((i2->unlimited_int[j]*i1->unlimited_int[k]) + dummy->unlimited_int[k] + carry)%10;
//             carry = ((i2->unlimited_int[j]*i1->unlimited_int[k]) + dummy->unlimited_int[k] + carry)/10;
//         }
//         dummy->unlimited_int[dummy->size] = carry;
//         while(dummy->unlimited_int[dummy->size]==0){
//             dummy->size--;
//         }
//         if(dummy->size == 0){
//             dummy->size = 0;
//             dummy->sign = 1;
//             dummy->unlimited_int[1] = 0;
//             dummy->unlimited_int[0] = 1;
//         }
//         i = add(i, dummy);
//         delete dummy;
//         delete copy;
//     }
//     return i;
// }

// //
// UnlimitedInt *UnlimitedInt ::mul(UnlimitedInt *i1, UnlimitedInt *i2)
// {
//     UnlimitedInt *i = new UnlimitedInt();
//     i->capacity = (i1->size + i2->size) + 1;
//     i->size = (i1->size + i2->size);
//     i->sign = i1->sign * i2->sign;
//     i->unlimited_int = new int[i->capacity];
//     i->unlimited_int[0] = i->sign;
//     int* product = new int[i->capacity];
//     int* carry = new int[i->capacity];
//     for(int a = 0; a<=i->size; a++){
//         product[a] = 0;
//         carry[a] = 0;
//     }
//     for(int j = 1; j<=i2->size; j++){
//         for(int k = 1; k<=i1->size; k++){
//             product[j+k-1] = product[j+k-1] + i1->unlimited_int[k]*i2->unlimited_int[j];
//             if(product[j+k-1]>=10){
//                 carry[j+k] = product[j+k-1]/10;
//                 product[j+k-1] = product[j+k-1]%10;
//             }
//         }
//     }
//     for(int j = 1; j<i1->size + i2->size; j++){
//         i->unlimited_int[j] = product[j] + carry[j];
//         if(i->unlimited_int[j]>=10){
//             carry[j+1] = carry[j+1] + i->unlimited_int[j]/10;
//             i->unlimited_int[j] = i->unlimited_int[j]%10;
//         }
//     }
//     i->unlimited_int[i1->size + i2->size] = carry[i1->size + i2->size] + product[i1->size + i2->size];
//     delete carry;
//     delete product;
//     return i;
// }

#include<iostream>
#include<vector>
using namespace std;

int main(){
    cout<<((-20)%3);
    return 0;
}


/* Do NOT add/remove any includes statements from this header file */
/* unless EXPLICTLY clarified on Piazza. */
#include "evaluator.h"
#include <vector>
#include<iostream>
Evaluator::Evaluator() {
    symtable = new SymbolTable();
}
Evaluator::~Evaluator() {
   //  cout<<"1\n";
    delete symtable;

   
    for (ExprTreeNode* node : expr_trees) {
        delete node;
    }
    expr_trees.clear();
}
void Evaluator::parse(vector<string> code){
   UnlimitedInt*zero=new UnlimitedInt("0");
  vector<ExprTreeNode*> stack;

  for (string token : code) {
    if (token == "(") {
    } else if (token == ")") {
      // Pop two nodes from the stack and make them the children of the current node.
     ExprTreeNode* right = stack.back();
      stack.pop_back();
      ExprTreeNode* op = stack.back();
      stack.pop_back();
      ExprTreeNode* left = stack.back();
      stack.pop_back();
      op->left = left;
      op->right = right;
      stack.push_back(op);
    } else {
      // Create a new node for the operand.
      ExprTreeNode* node = new ExprTreeNode(token,zero);
      stack.push_back(node);
    }
  }
   ExprTreeNode* right = stack.back();
  stack.pop_back();
   ExprTreeNode*root=stack.back();
   stack.pop_back();
   ExprTreeNode*left=stack.back();
   stack.pop_back();
   root->left=left;
   root->right=right;
  expr_trees.push_back(root);
  // The root of the parse tree is the last node on the stack.
}
void printtable(ExprTreeNode*s){
     if(s==NULL){
      return;
     }
       if(s->left!=NULL){
        // cout<<"printing left\n";
       printtable(s->left);
       }
       //cout<<"printing val\n";
       cout<<s->val->get_frac_str()<<endl;
       if(s->right!=NULL){
       //  cout<<"printing right\n";
       printtable(s->right);
       }
 }
 UnlimitedRational*evaluatedval(ExprTreeNode*root,SymbolTable*sym){
      if(root->type=="VAL"){
         return root->val;
      }
      if(root->type=="ADD"){
        UnlimitedRational*left=evaluatedval(root->left,sym);
        UnlimitedRational*right=evaluatedval(root->right,sym);
        return left->add(left,right);
      }else if(root->type=="SUB"){
         UnlimitedRational*left=evaluatedval(root->left,sym);
        UnlimitedRational*right=evaluatedval(root->right,sym);
        return left->sub(left,right);
      }else if(root->type=="MUL"){
         UnlimitedRational*left=evaluatedval(root->left,sym);
        UnlimitedRational*right=evaluatedval(root->right,sym);
        return left->mul(left,right);
      }else if(root->type=="DIV"){
         UnlimitedRational*left=evaluatedval(root->left,sym);
        UnlimitedRational*right=evaluatedval(root->right,sym);
        return left->div(left,right);
      }else if(root->type=="MOD"){
         UnlimitedRational*left=evaluatedval(root->left,sym);
        UnlimitedRational*right=evaluatedval(root->right,sym);
         UnlimitedInt*n=left->get_p();
         UnlimitedInt*m=right->get_p();
         UnlimitedInt*one=right->get_q();
         UnlimitedInt*ans=n->mod(n,m);
         return new UnlimitedRational(ans,one);
      }else if(root->type=="VAR"){
         string k=root->id;
           return sym->search(k);
      }
        UnlimitedInt*one=new UnlimitedInt("0");
           UnlimitedInt*on=new UnlimitedInt("1");
           UnlimitedRational* val=new UnlimitedRational(one,on);
            return val;
 }
void Evaluator:: eval(){
     ExprTreeNode*traveller=expr_trees.back();
     traveller->evaluated_value=evaluatedval(traveller->right,symtable);
     // cout<<evaluatedval(traveller->right)->get_frac_str()<<endl;
     symtable->insert(traveller->left->id,traveller->evaluated_value);
}
int main(){
   Evaluator p;
  vector<string> code;
code.push_back("v");
code.push_back(":=");
code.push_back("(");
code.push_back("13");
code.push_back("+");
code.push_back("2");
code.push_back(")");
// for(string i:code){
  //  cout<<i<<endl;
 //}
      p.parse(code);
      p.eval();
      cout<<p.symtable->search("v")->get_frac_str()<<endl;
    //  printtable(p.expr_trees.back());
    return 0;
}

/* Do NOT add/remove any includes statements from this header file */
/* unless EXPLICTLY clarified on Piazza. */
#include "evaluator.h"
#include <vector>
#include "ExprTreeNode.h"
#include <iostream>

void inOrderTraversal(ExprTreeNode* root) {
    if (root == nullptr) {
        cout<<"null"<<endl;
        return;
    }
    cout<<"notnull"<<endl;;
    // Traverse the left subtree
    inOrderTraversal(root->left);
    
    // Process the current node (print its value)
    std::cout << root->type<< " ";
    
    // Traverse the right subtree
    inOrderTraversal(root->right);
}

class Stack
{
public:
    std::vector<ExprTreeNode *> data;
    Stack() {}

    ~Stack()
    {
        while (!data.empty())
        {
            ExprTreeNode *node = data.back();
            data.pop_back();
            delete node;
        }
    }

    bool isEmpty() const
    {
        return data.empty();
    }

    void push(ExprTreeNode *node)
    {
        data.push_back(node);
    }

    ExprTreeNode *pop()
    {
        if (!isEmpty())
        {
            ExprTreeNode *topNode = data.back();
            data.pop_back();
            return topNode;
        }
        return nullptr;
    }

    ExprTreeNode *top() const
    {
        if (!isEmpty())
        {
            return data.back();
        }
        return nullptr;
    }
};

Evaluator::Evaluator()
{
    symtable = new SymbolTable();
}

Evaluator::~Evaluator()
{
    for (int i = expr_trees.size() - 1; i >= 0; i--)
    {
        ExprTreeNode *temp = expr_trees[i];
        delete temp;
    }
}

void Evaluator::parse(vector<string> code)
{
    Stack s;
    ExprTreeNode *root = new ExprTreeNode();
    root->type = "dummy";
    root->id = code[1];
    ExprTreeNode *rootleft = new ExprTreeNode();
    rootleft->type = "VAR";
    rootleft->id = code[0];
    root->left = rootleft;
    s.push(rootleft);
    s.push(root);
    ExprTreeNode *rootright = new ExprTreeNode();
    root->right = rootright;
    s.push(rootright);
    for (int i = 2; i < code.size(); i++)
    {
        if (code[i] == "(")
        {
            ExprTreeNode *currnode = s.top();
            ExprTreeNode *newnode = new ExprTreeNode();
            currnode->left = newnode;
            s.push(newnode);
            cout<<code[i];
        }
        else if (code[i] == "+")
        {
            ExprTreeNode *currnode = s.top();
            currnode->type = "ADD";
            ExprTreeNode *newnode = new ExprTreeNode();
            currnode->right = newnode;
            currnode->id = "+";
            s.push(newnode);
            cout<<code[i];
        }
        else if (code[i] == "-")
        {
            ExprTreeNode *currnode = s.top();
            currnode->type = "SUB";
            ExprTreeNode *newnode = new ExprTreeNode();
            currnode->right = newnode;
            currnode->id = "-";
            s.push(newnode);
            cout<<code[i];
        }
        else if (code[i] == "*")
        {
            ExprTreeNode *currnode = s.top();
            currnode->type = "MUL";
            ExprTreeNode *newnode = new ExprTreeNode();
            currnode->right = newnode;
            currnode->id = "*";
            s.push(newnode);
            cout<<code[i];
        }
        else if (code[i] == "/")
        {
            ExprTreeNode *currnode = s.top();
            currnode->type = "DIV";
            ExprTreeNode *newnode = new ExprTreeNode();
            currnode->right = newnode;
            currnode->id = "/";
            s.push(newnode);
            cout<<code[i];
        }
        else if (code[i][0] == '-' && isdigit(code[i][1]))
        {
            ExprTreeNode *currnode = s.top();
            currnode->type = "VAL";
            currnode->val = new UnlimitedRational(new UnlimitedInt(code[i]), new UnlimitedInt("1"));
            currnode->evaluated_value = new UnlimitedRational(new UnlimitedInt(code[i]), new UnlimitedInt("1"));
            if (currnode->val->get_q_str() == "1")
            {
                currnode->id = currnode->val->get_p_str();
            }
            else
            {
                currnode->id = currnode->val->get_frac_str();
            }
            s.pop();
            cout<<code[i];
        }
        else if (isdigit(code[i][0]))
        {
            ExprTreeNode *currnode = s.top();
            currnode->type = "VAL";
            currnode->val = new UnlimitedRational(new UnlimitedInt(code[i]), new UnlimitedInt("1"));
            currnode->evaluated_value = new UnlimitedRational(new UnlimitedInt(code[i]), new UnlimitedInt("1"));
            if (currnode->val->get_q_str() == "1")
            {
                currnode->id = currnode->val->get_p_str();
            }
            else
            {
                currnode->id = currnode->val->get_frac_str();
            }
            s.pop();
            cout<<code[i];
        }
        else if (code[i] == ")")
        {
            s.pop();
            cout<<code[i];
        }
        else{
            ExprTreeNode* currnode = s.top();
            currnode->id = code[i];
            currnode->type = "VAR";
            s.pop();
            cout<<code[i];
        }
    }
    expr_trees.push_back(root);
    cout<<1;
}

UnlimitedRational *calc(ExprTreeNode *i1, SymbolTable *symtable)
{
    if (i1->right == nullptr)
    {
        return nullptr;
    }
    else if (i1->right->type == "ADD")
    {
        UnlimitedRational *temp = UnlimitedRational::add(calc(i1->right->right, symtable), calc(i1->right->left, symtable));
        i1->right->evaluated_value = temp;
        return temp;
    }
    else if (i1->right->type == "MUL")
    {
        UnlimitedRational *temp = UnlimitedRational::mul(calc(i1->right->right, symtable), calc(i1->right->left, symtable));
        i1->right->evaluated_value = temp;
        return temp;
    }
    else if (i1->right->type == "SUB")
    {
        UnlimitedRational *temp = UnlimitedRational::sub(calc(i1->right->left, symtable), calc(i1->right->right, symtable));
        i1->right->evaluated_value = temp;
        return temp;
    }
    else if (i1->right->type == "DIV")
    {
        UnlimitedRational *temp = UnlimitedRational::div(calc(i1->right->left, symtable), calc(i1->right->right, symtable));
        i1->right->evaluated_value = temp;
        return temp;
    }
    else if (i1->right->type == "VAL")
    {
        return i1->right->evaluated_value;
    }
    else if (i1->right->type == "VAR")
    {
        if (symtable->search(i1->right->id) != NULL)
        {
            return symtable->search(i1->right->id);
        }
        // else
        // {
        //     symtable->insert(i1->right->type,i1->right->evaluated_value);
        // }
    }
}

void Evaluator::eval()
{
    string vari = expr_trees.back()->left->id;
    ExprTreeNode *mainnode = expr_trees.back();
    UnlimitedRational *ans = calc(mainnode, symtable);
    symtable->insert(vari, ans);
}

int main()
{
    Evaluator *e = new Evaluator();
    cout << 1 << endl;
    vector<string> s = {"x1", ":=", "(", "(", "213124", "+", "4561561", ")", "/", "(", "250", "/", "25", ")", ")"};
    cout << 1 << endl;

    vector<string> s1 = {"x2", ":=", "(", "x1", "*", "10", ")"};
    cout << 1 << endl;

    e->parse(s);
    cout << "hogaya" << 1 << endl;
    cout<<e->expr_trees.size();
    // for(int i = 0; i<e->expr_trees.size(); i++){
    //     cout<<e->expr_trees[i]->type<<endl;
    // }
    e->eval();
    cout << 1 << endl;

    e->parse(s1);
    
    inOrderTraversal(e->expr_trees[0]);
    cout << 1 << endl;

    e->eval();
    cout << "evrthing fine:\n";
    delete e;
    cout << "impossible\n";
    return 0;
}

// int main()
// {
//     // Create an Evaluator object
//     Evaluator *e = new Evaluator();

//     // Define the expression as a vector of strings
//     vector<string> expression = {"x1", ":=", "(", "(", "2", "+", "3", ")", "*", "4", ")"};

//     // Parse the expression
//     e->parse(expression);

//     // Get the expression tree
//     ExprTreeNode *root = e->expr_trees.back();

//     // Print the infix notation of the expression
//     cout << "Infix Notation: ";
//     inordernotation(root);

//     // Clean up
//     delete e;

//     return 0;
// }
