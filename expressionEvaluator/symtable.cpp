/* Do NOT add/remove any includes statements from this header file */
/* unless EXPLICTLY clarified on Piazza. */
#include "symtable.h"

SymEntry *searchrecursively(SymEntry *&root, string k)
{
    if (root == nullptr)
    {
        return nullptr;
    }
    else if (root->key == k)
    {
        return root;
    }
    else if (root->key < k)
    {
        return searchrecursively(root->right, k);
    }
    else
    {
        return searchrecursively(root->left, k);
    }
}

SymbolTable::SymbolTable()
{
    size = 0;
    root = nullptr;
}

SymbolTable ::~SymbolTable()
{
    if (root->right != nullptr)
    {
        delete root->right;
    }
    if (root->left != nullptr)
    {
        delete root->left;
    }
    delete root;
}

void insertionrecursive(SymEntry *&root, string k, UnlimitedRational *v)
{
    if (root == nullptr)
    {
        root = new SymEntry(k, v);
    }
    else if (root->key < k)
    {
        insertionrecursive(root->right, k, v);
    }
    else if (root->key > k)
    {
        insertionrecursive(root->left, k, v);
    }
}

void SymbolTable ::insert(string k, UnlimitedRational *v)
{
    insertionrecursive(root, k, v);
    size = size + 1;
}

SymEntry *successor(SymEntry *root)
{
    if (root == nullptr)
    {
        return nullptr;
    }
    else if (root->right == nullptr)
    {
        return nullptr;
    }
    SymEntry *curr = root->right;
    while (curr != nullptr && curr->left != nullptr)
    {
        curr = curr->left;
    }
    return curr;
}

SymEntry *removerecursively(SymEntry *&root, string k)
{
    if (root == nullptr)
    {
        return root;
    }
    else if (root->key > k)
    {
        root->left = removerecursively(root->left, k);
    }
    else if (root->key < k)
    {
        root->right = removerecursively(root->right, k);
    }
    else
    {
        if (root->left == nullptr)
        {
            SymEntry *dummy = root->right;
            delete root;
            return dummy;
        }
        else if (root->right == nullptr)
        {
            SymEntry *dummy = root->left;
            delete root;
            return dummy;
        }
        SymEntry *dummy = successor(root);
        root->key = dummy->key;
        root->val = dummy->val;
        root->right = removerecursively(root->right, dummy->key);
    }
    return root;
}

void SymbolTable::remove(string k)
{
    if (searchrecursively(root, k) != nullptr)
    {
        root = removerecursively(root, k);
        size = size - 1;
    }
}

UnlimitedRational *SymbolTable::search(string k)
{
    SymEntry *temp = searchrecursively(root, k);
    if (temp == nullptr)
    {
        return nullptr;
    }
    else
    {
        return temp->val;
    }
}

int SymbolTable::get_size()
{
    return size;
}

SymEntry *SymbolTable::get_root()
{
    return root;
}

