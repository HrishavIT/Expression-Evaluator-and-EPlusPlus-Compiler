/* Do NOT add/remove any includes statements from this header file */
/* unless EXPLICTLY clarified on Piazza. */
#include "eppcompiler.h"

// Write your code below this line

EPPCompiler::EPPCompiler()
{
    memory_size = 0;
    output_file = "";
}

EPPCompiler::EPPCompiler(string out_file, int mem_limit)
{
    output_file = out_file;
    memory_size = mem_limit;
    for (int i = memory_size - 1; i >= 0; i--)
    {
        mem_loc.push_back(i);
    }
}

void EPPCompiler::compile(vector<vector<string>> code)
{
    for (int i = 0; i<code.size(); i++)
    {
        targ.parse(code[i]);
        ExprTreeNode *temp = targ.expr_trees.back();
        if (temp->left->type == "DEL")
        {
            mem_loc.push_back(targ.symtable->search(temp->right->id));
            targ.last_deleted = targ.symtable->search(temp->right->id);
            targ.symtable->remove(temp->right->id);
        }
        else if (temp->left->type == "VAR")
        {
            if (targ.symtable->search(temp->left->id) != -2){

            }
            else
            {
                targ.symtable->insert(temp->left->id);
                targ.symtable->assign_address(temp->left->id, mem_loc.back());
                mem_loc.pop_back();
            }
        }
        vector<string> finalans = generate_targ_commands();
        write_to_file(finalans);
    }
}

void helper_targ_command(SymbolTable *sym, ExprTreeNode *node, vector<string> &code)
{
    if (node->type == "VAL")
    {
        code.push_back("PUSH " + to_string(node->num));
    }
    else if (node->type == "VAR")
    {
        code.push_back("PUSH mem[" + to_string(sym->search(node->id)) + "]");
    }
    else
    {
        helper_targ_command(sym, node->right, code);
        helper_targ_command(sym, node->left, code);
        code.push_back(node->type);
    }
}

vector<string> EPPCompiler::generate_targ_commands()
{
    vector<string> res;
    ExprTreeNode *temp = targ.expr_trees.back();
    if (temp->left->type == "RET")
    {
        helper_targ_command(targ.symtable, temp->right, res);
        res.push_back("RET = POP");
    }
    if (temp->left->type == "DEL")
    {
        string to_be_deleted = to_string(targ.last_deleted);
        string to_be_pushed = "DEL = mem[" + to_be_deleted + "]";
        res.push_back(to_be_pushed);
    }
    else if (temp->left->type == "VAR")
    {
        helper_targ_command(targ.symtable, temp->right, res);
        string var = temp->left->id;
        int address = targ.symtable->search(var);
        string to_be_searched = to_string(address);
        string to_be_pushed = "mem[" + to_be_searched + "] = POP";
        res.push_back(to_be_pushed);
    }
    
    return res;
}

void EPPCompiler::write_to_file(vector<string> commands)
{
    ofstream file(output_file, std::ios::app);
    for (int i = 0; i < commands.size(); i++)
    {
        file << commands[i] << endl;
    }
    file.close();
}

EPPCompiler::~EPPCompiler()
{
    targ.expr_trees.clear();
    delete targ.symtable;
}

