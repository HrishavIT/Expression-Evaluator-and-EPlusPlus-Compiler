/* Do NOT add/remove any includes statements from this header file */
/* unless EXPLICTLY clarified on Piazza. */
#include "symtable.h"

void deletetree(SymNode *root)
{
    if (root == NULL)
    {
        return;
    }
    deletetree(root->left);
    deletetree(root->right);
    delete root;
}

SymbolTable::SymbolTable()
{
}

int height(SymNode *root)
{
    if (root == NULL)
    {
        return 0;
    }
    else if (root->left == NULL && root->right == NULL)
    {
        return 1;
    }
    else
    {
        return 1 + max(height(root->left), height(root->right));
    }
}

string maxstr(string a, string b)
{
    if (a >= b)
    {
        return a;
    }
    else
    {
        return b;
    }
}

string minstr(string a, string b)
{
    if (a <= b)
    {
        return a;
    }
    else
    {
        return b;
    }
}

string maxval(SymNode *root)
{
    if (root == NULL)
    {
        return "";
    }
    else
    {
        string val = root->key;
        string leftmax = maxval(root->left);
        string rightmax = maxval(root->right);
        return maxstr(val, maxstr(leftmax, rightmax));
    }
}

string minval(SymNode *root)
{
    if (root == NULL)
    {
        return "";
    }
    else
    {
        string val = root->key;
        string leftmin = minval(root->left);
        string rightmin = minval(root->right);
        return minstr(val, minstr(leftmin, rightmin));
    }
}

bool bst(SymNode *root)
{
    if (root == NULL)
    {
        return true;
    }
    if (root->left != NULL && maxval(root->left) >= root->key)
    {
        return false;
    }
    if (root->right != NULL && minval(root->right) <= root->key)
    {
        return false;
    }
    if (bst(root->right) == false)
    {
        return false;
    }
    if (bst(root->left) == false)
    {
        return false;
    }
    return true;
}

int mod(int a)
{
    if (a >= 0)
    {
        return a;
    }
    else
    {
        return (-1 * a);
    }
}

void updateheight(SymNode *root)
{
    if (root != NULL)
    {
        int val = 1;
        if (root->left != NULL)
        {
            val = root->left->height + 1;
        }
        if (root->right != NULL)
        {
            val = max(val, root->right->height + 1);
        }
        root->height = val;
    }
}

bool avl(SymNode *root)
{
    if (root == NULL)
    {
        return true;
    }
    if (root->left == NULL && root->right == NULL)
    {
        return true;
    }
    if (bst(root) == false)
    {
        return false;
    }
    if (mod(height(root->left) - height(root->right)) > 1)
    {
        return false;
    }
    if (avl(root->left) == false)
    {
        return false;
    }
    if (avl(root->right) == false)
    {
        return false;
    }
    return true;
}

SymNode *leftleftrotationllr(SymNode *root)
{
    SymNode *temp = root->left;
    root->left = temp->right;
    if (temp->right != NULL)
    {
        temp->right->par = root;
    }
    temp->right = root;
    temp->par = root->par;
    root->par = temp;
    if (temp->par != NULL)
    {
        temp->par->right = temp;
    }
    root = temp;
    updateheight(root->left);
    updateheight(root->right);
    updateheight(root);
    updateheight(root->par);
    return root;
}

SymNode *rightrightrotationrrr(SymNode *root)
{
    SymNode *temp = root->right;
    root->right = temp->left;
    if (temp->left != NULL)
    {
        temp->left->par = root;
    }
    temp->left = root;
    temp->par = root->par;
    root->par = temp;
    if (temp->par != NULL && root->key < temp->par->key)
    {
        temp->par->left = temp;
    }
    else
    {
        if (temp->par != NULL)
        {
            temp->par->right = temp;
        }
    }
    root = temp;
    updateheight(root->left);
    updateheight(root->right);
    updateheight(root);
    updateheight(root->par);
    return root;
}

SymNode *leftrightrotationlrr(SymNode *root)
{
    root->left = rightrightrotationrrr(root->left);
    return leftleftrotationllr(root);
}

SymNode *rightleftrotationrlr(SymNode *root)
{
    root->right = leftleftrotationllr(root->right);
    return rightrightrotationrrr(root);
}

SymNode *insertrecursively(SymNode *root, SymNode *parent, string k)
{
    if (root == NULL)
    {
        root = new SymNode(k);
    }
    else if (root->key > k)
    {
        root->left = insertrecursively(root->left, root, k);
        // root->left->par = root;
        int leftsubheight = 0;
        int rightsubheight = 0;
        if (root->left != NULL)
        {
            leftsubheight = root->left->height;
        }
        if (root->right != NULL)
        {
            rightsubheight = root->right->height;
        }
        if (mod(leftsubheight - rightsubheight) == 2)
        {
            if (root->left != NULL && k < root->left->key)
            {
                root = leftleftrotationllr(root);
            }
            else
            {
                root = leftrightrotationlrr(root);
            }
        }
    }
    else if (root->key < k)
    {
        root->right = insertrecursively(root->right, root, k);
        root->right->par = root;
        int leftsubheight = 0;
        int rightsubheight = 0;
        if (root->left != NULL)
        {
            leftsubheight = root->left->height;
        }
        if (root->right != NULL)
        {
            rightsubheight = root->right->height;
        }
        if (mod(leftsubheight - rightsubheight) == 2)
        {
            if (root->right != NULL && k < root->right->key)
            {
                root = rightleftrotationrlr(root);
            }
            else
            {
                root = rightrightrotationrrr(root);
            }
        }
    }
    updateheight(root);
    return root;
}

void SymbolTable::insert(string k)
{
    if (search(k) == -2)
    {
        root = insertrecursively(root, NULL, k);
        size = size + 1;
        return;
    }
    return;
}

SymNode *searchrecursively(SymNode *root, string k)
{
    if (root == NULL)
    {
        return root;
    }
    else if (root->key == k)
    {
        return root;
    }
    else if (root->key > k)
    {
        return searchrecursively(root->left, k);
    }
    else
    {
        return searchrecursively(root->right, k);
    }
}

SymNode *balancetree(SymNode *root)
{
    int leftsubheight = 0;
    int rightsubheight = 0;
    if (root->left != NULL)
    {
        leftsubheight = root->left->height;
    }
    if (root->right != NULL)
    {
        rightsubheight = root->right->height;
    }
    if (mod(rightsubheight - leftsubheight) == 2)
    {
        if (leftsubheight < rightsubheight)
        {
            int rightheight1 = 0;
            int rightheight2 = 0;
            if (root->right->right != NULL)
            {
                rightheight2 = root->right->right->height;
            }
            if (root->right->left != NULL)
            {
                rightheight1 = root->right->left->height;
            }
            if (rightheight1 > rightheight2)
            {
                root = rightleftrotationrlr(root);
            }
            else
            {
                root = rightrightrotationrrr(root);
            }
        }
        else
        {
            int leftheight1 = 0;
            int leftheight2 = 0;
            if (root->left->right != NULL)
            {
                leftheight2 = root->left->right->height;
            }
            if (root->left->left != NULL)
            {
                leftheight1 = root->left->left->height;
            }
            if (leftheight1 > leftheight2)
            {
                root = leftleftrotationllr(root);
            }
            else
            {
                root = leftrightrotationlrr(root);
            }
        }
    }
    return root;
}

SymNode *removerecursively(SymNode *root, string k)
{
    if (root != NULL)
    {
        if (root->key == k)
        {
            if (root->right == NULL && root->left != NULL)
            {
                if (root->par != NULL)
                {
                    if (root->par->key < root->key)
                    {
                        root->par->right = root->left;
                    }
                    else
                    {
                        root->par->left = root->left;
                    }
                    updateheight(root->par);
                }
                root->left->par = root->par;
                root->left = balancetree(root->left);
                return root->left;
            }
            else if (root->left == NULL && root->right != NULL)
            {
                if (root->par != NULL)
                {
                    if (root->par->key < root->key)
                    {
                        root->par->right = root->right;
                    }
                    else
                    {
                        root->par->left = root->right;
                    }
                    updateheight(root->par);
                }
                root->right->par = root->par;
                root->right = balancetree(root->right);
                return root->right;
            }
            else if (root->left == NULL && root->right == NULL)
            {
                if (root->par->key < root->key)
                {
                    root->par->right = NULL;
                }
                else
                {
                    root->par->left = NULL;
                }
                if (root->par != NULL)
                {
                    updateheight(root->par);
                }
                root = NULL;
                return root;
            }
            else
            {
                SymNode *temp = root;
                temp = temp->right;
                while (temp->left != NULL)
                {
                    temp = temp->left;
                }
                string val = temp->key;
                root->right = removerecursively(root->right, temp->key);
                root->key = val;
                root = balancetree(root);
            }
        }
        else if (root->key < k)
        {
            root->right = removerecursively(root->right, k);
            root = balancetree(root);
        }
        else if (root->key > k)
        {
            root->left = removerecursively(root->left, k);
            root = balancetree(root);
        }
        if (root != NULL)
        {
            updateheight(root);
        }
    }
    return root;
}

void SymbolTable::remove(string k)
{
    if (search(k) != -2)
    {
        root = removerecursively(root, k);
        size = size - 1;
    }
}

int SymbolTable::search(string k)
{
    if (searchrecursively(root, k) == NULL)
    {
        return -2;
    }
    else
    {
        return searchrecursively(root, k)->address;
    }
}

void SymbolTable::assign_address(string k, int idx)
{
    searchrecursively(root, k)->address = idx;
}

int SymbolTable::get_size()
{
    return size;
}

SymNode *SymbolTable::get_root()
{
    return root;
}

SymbolTable::~SymbolTable()
{
    deletetree(root);
}
