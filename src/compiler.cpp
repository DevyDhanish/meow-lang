#include "../include/compiler.hpp"
#include "../include/tree.hpp"
#include "../include/token.hpp"
#include "../include/bytecode.hpp"
#include <iostream>
#include <vector>

// x = y + 10;
// push y
// push 10
// add
// store x

void resolveExpr(std::vector<bytecode> &bcv, Tree root)
{
    if(root.data._TOKEN_TYPE != _TOKEN_PLUS)
    {
        bcv.push_back(makebytecode(PUSH, root.data));
    }

    for(size_t i = 0; i < root.childs.size(); i++)
    {
        resolveExpr(bcv, root.get_child(i));
    }
}

void Compiler::genAssignmentBc(std::vector<bytecode> &bc, Tree root)
{
    resolveExpr(bc, root);
}

void Compiler::compile(std::vector<bytecode> byte_vector, Tree root) {
    if(root.data._TOKEN_TYPE == _TOKEN_VAR)
    {
        Token lval = root.data;
        if(root.get_child(0).data._TOKEN_TYPE == _TOKEN_EQU)
        {
            genAssignmentBc(byte_vector, root.get_child(0).get_child(0));
        }

        // after
        byte_vector.push_back(makebytecode(STORE, lval));
    }

    for(size_t i = 0; i < byte_vector.size(); i++)
    {   
        std::cout << byte_vector[i].mnemonic << "," << byte_vector[i].operand._TOKEN_VALUE;
        std::cout << "\n";
    }
}