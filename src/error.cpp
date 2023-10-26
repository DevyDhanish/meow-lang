#include "../include/error.hpp"
#include <unordered_map>
#include "../include/token.hpp"
#include "../include/vm.hpp"
#include <iostream>
#include <vector>

std::unordered_map<Error_T, std::string> error_table = 
{
    {_E_SYNTAX_ERROR, "\nSyntax Error at %lu : %s\n"},
    {_E_CMP_ERROR, "\nComparison Error at %lu : %s\n"},
    {_E_TYPE_ERROR, "\nType Error at %lu : %s\n"},
    {_E_INDENTATION_ERROR, "\nIndentation Error at %lu : %s\n"},
    {_E_UNKNOW_TOKEN_ERROR, "\nUnknow Token at %lu : %s\n"},
    {_E_UNDECLARED_VAR_ERROR, "\nUndeclared Variable at %lu : %s\n"},
};

int counter = 0;
std::vector<Token> TOKENS;

void displayError(Error_T error_type, std::string _line, size_t line_number) {
    printf(error_table[error_type].c_str(), line_number, _line.c_str());
    printf("\n");
    exit(0);
}

// Token advance()
// {
//     if(counter < TOKENS.size())
//     {
//         return TOKENS[counter];
//         counter++;
//     }
//     else
//     {
//         return makeToken(_TOKEN_EMPTY, "", "", 0, 0);
//     }
// }

// void errorIfNextTokenInvalid(std::vector<TOKEN_T> allowed_next_tokens_t, TOKEN_T next_TOKEN_TYPE)
// {
//     if(std::find(allowed_next_tokens_t.begin(), allowed_next_tokens_t.end(), next_TOKEN_TYPE) == allowed_next_tokens_t.end())
//     {
//         displayError(_E_SYNTAX_ERROR, "", 1);
//     }
// }

// Token lookAhead()
// {
//     return makeToken(_TOKEN_EMPTY, "", "", 0, 0);
// }

// void checkSyntax(std::vector<Token> tokens)
// {
//     TOKENS = tokens;


// }