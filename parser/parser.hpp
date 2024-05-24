#pragma once

#include "../include/internals/mewcore_ast.hpp"
#include <vector>
#include "../include/token.hpp"

enum _rule { File_Rule, };

struct Parser
{
    std::vector<Token> tokens;
    size_t counter;
    size_t level;
};

typedef Parser Parser;

void *expression_rule(Parser &p, int prec);
void *parse(const std::vector<Token> &tok_list, _rule rule);
struct Parser gen_parser(const std::vector<Token> &toks, size_t c, size_t l);