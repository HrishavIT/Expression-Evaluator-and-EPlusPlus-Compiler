/* Do NOT add/remove any includes statements from this header file */
/* unless EXPLICTLY clarified on Piazza. */
#include "parser.h"

// Write your code below this line
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
            ExprTreeNode *newnode = new ExprTreeNode("VAL", stoi(code[0]));
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

Parser::Parser()
{
    symtable = new SymbolTable();
}

void Parser::parse(vector<string> expression)
{
    //     // ExprTreeNode *root = new ExprTreeNode();
    //     // root->type = "dummy";
    //     // root->id = expression[1];
    //     // ExprTreeNode *leftroot = new ExprTreeNode();
    //     // if (expression[0] == "del")
    //     // {
    //     //     leftroot->type = "DEL";
    //     //     leftroot->id = expression[0];
    //     //     root->left = leftroot;
    //     //     ExprTreeNode *rightroot = new ExprTreeNode();
    //     //     rightroot->id = expression[2];
    //     //     rightroot->type = "VAR";
    //     //     root->right = rightroot;
    //     // }
    //     // else if (expression[0] == "ret")
    //     // {
    //     //     leftroot->type = "RET";
    //     //     leftroot->id = expression[0];
    //     //     root->left = leftroot;
    //     //     ExprTreeNode *rightroot = new ExprTreeNode();
    //     //     vector<string> temp(expression.begin() + 2, expression.end());
    //     //     root->right = treemaker(temp);
    //     //     root->right = rightroot;
    //     // }
    //     // else
    //     // {
    //     //     leftroot->type = "VAR";
    //     //     leftroot->id = expression[0];
    //     //     root->left = leftroot;
    //     //     vector<string> temp(expression.begin() + 2, expression.end());
    //     //     root->right = treemaker(temp);
    //     // }
    //     // expr_trees.push_back(root);
    string var1 = expression[0];
    string var2 = expression[1];
    vector<string> temp(expression.begin() + 2, expression.end());
    ExprTreeNode *root = new ExprTreeNode();
    root->right = treemaker(temp);
    ExprTreeNode *leftnode = new ExprTreeNode();
    if (expression[0] == "del")
    {
        leftnode->type = "DEL";
    }
    else if (expression[0] == "ret")
    {
        leftnode->type = "RET";
    }
    else
    {
        leftnode->type = "VAR";
        leftnode->id = expression[0];
    }
    root->left = leftnode;
    root->type = "dummy";
    expr_trees.push_back(root);
}

Parser::~Parser()
{
    expr_trees.clear();
}

// // need to add del and ret statements
/* Do NOT add/remove any includes statements from this header file */
/* unless EXPLICTLY clarified on Piazza. */
