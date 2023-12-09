#include "../../include/compiler.hpp"
#include "../../include/token.hpp"

void Compiler::advance()
{
    if(counter < tokens.size())
    {
        prev = current;
        current = tokens[counter];
        counter++;
    }
    else
    {
        return;
    }
}

COMPILER_RESULT Compiler::compile()
{

}