/* Do NOT add/remove any includes statements from this header file */
/* unless EXPLICITLY clarified on Piazza. */
#include "evaluator.h"
#include "exprtreenode.h"
#include <vector>
#include<iostream>

class Stack
{
public:
    vector<string> s;
    int size;

    Stack()
    {
        size = 0;
    }

    ~Stack()
    {
        s.clear();
    }

    void push(string k)
    {
        s.push_back(k);
        size++;
    }

    bool empty()
    {
        if (size != 0)
        {
            return false;
        }
        return true;
    }

    void pop()
    {
        if (!empty())
        {
            s.pop_back();
            size--;
        }
    }

    string top()
    {
        if (!empty())
        {
            string p = s[size - 1];
            return p;
        }
    }
};

Evaluator::Evaluator()
{
    symtable = new SymbolTable();
}

Evaluator::~Evaluator()
{
    expr_trees.clear();
}

bool integer(string &s)
{
    if (s[0] == '-')
    {
        if (isdigit(s[1]))
        {
            return true;
        }
    }
    else
    {
        if (isdigit(s[0]))
        {
            return true;
        }
    }
    return false;
}

ExprTreeNode *treemaker(vector<string> code)
{
    if (code[0] == "(")
    {
        code.erase(code.begin());
        code.pop_back();
    }
    if (code.size() == 1)
    {
        if (integer(code[0]))
        {
            ExprTreeNode *newnode = new ExprTreeNode("VAL", new UnlimitedInt(code[0]));
            return newnode;
        }
        else
        {
            ExprTreeNode *newnode = new ExprTreeNode();
            newnode->type = "VAR";
            newnode->id = code[0];
            return newnode;
        }
    }
    else
    {
        Stack st;
        string s;
        int index = 0;
        for (string token : code)
        {
            if (token == "(")
            {
                st.push(token);
            }
            else if (token == ")")
            {
                st.pop();
            }
            else if (st.empty())
            {
                if (token == "+" || token == "-" || token == "*" || token == "/")
                {
                    break;
                }
            }
            index = index + 1;
        }

        ExprTreeNode *newnode = new ExprTreeNode();
        vector<string> leftstringvec(code.begin(), code.begin() + index);
        vector<string> rightstringvec(code.begin() + index + 1, code.end());

        newnode->left = treemaker(leftstringvec);
        newnode->right = treemaker(rightstringvec);
        if (code[index] == "+")
        {
            newnode->type = "ADD";
        }
        else if (code[index] == "-")
        {
            newnode->type = "SUB";
        }
        else if (code[index] == "*")
        {
            newnode->type = "MUL";
        }
        else if (code[index] == "/")
        {
            newnode->type = "DIV";
        }
        return newnode;
    }
    return nullptr;
}

void Evaluator::parse(std::vector<std::string> code)
{
    ExprTreeNode *root = new ExprTreeNode();
    root->type = "dummy";
    root->id = code[1];
    ExprTreeNode *leftroot = new ExprTreeNode();
    leftroot->type = "VAR";
    leftroot->id = code[0];
    root->left = leftroot;
    vector<string> temp(code.begin() + 2, code.end());
    root->right = treemaker(temp);
    expr_trees.push_back(root);
}

UnlimitedRational *calc(ExprTreeNode *i1, SymbolTable *symtable)
{
    if (i1 == nullptr)
    {
        return nullptr;
    }
    else if (i1->type == "ADD")
    {
        UnlimitedRational *temp = UnlimitedRational::add(calc(i1->right, symtable), calc(i1->left, symtable));
        i1->evaluated_value = temp;
        return temp;
    }
    else if (i1->type == "MUL")
    {
        UnlimitedRational *temp = UnlimitedRational::mul(calc(i1->right, symtable), calc(i1->left, symtable));
        i1->evaluated_value = temp;
        return temp;
    }
    else if (i1->type == "SUB")
    {
        UnlimitedRational *temp = UnlimitedRational::sub(calc(i1->left, symtable), calc(i1->right, symtable));
        i1->evaluated_value = temp;
        return temp;
    }
    else if (i1->type == "DIV")
    {
        UnlimitedRational *temp = UnlimitedRational::div(calc(i1->left, symtable), calc(i1->right, symtable));
        i1->evaluated_value = temp;
        return temp;
    }
    else if (i1->type == "VAL")
    {
        return i1->val;
    }
    else if (i1->type == "VAR")
    {
        UnlimitedRational *temp = symtable->search(i1->id);
        i1->evaluated_value = temp;
        return i1->evaluated_value;
    }
    return nullptr;
}

void Evaluator::eval()
{
    string var_name = expr_trees.back()->left->id;
    UnlimitedRational *res = calc(expr_trees.back()->right, symtable);
    symtable->insert(var_name, res);
}
