#pragma once

#include "tree.hpp"
#include "token.hpp"
#include "vm.hpp"

class Interpreter{
    public:
        void convertToByteCode(Tree root);

    private:
        void generateAssignmentByteCode(Token op, Tree op1, Tree op2);
        void generateShowByteCode(Token op, Tree op1);
};