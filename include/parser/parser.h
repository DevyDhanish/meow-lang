#ifndef PARSER_H
#define PARSER_H

#include "../DS/tree.h"
#include "../DS/list.h"

// Used to generate a AST ( Abstract syntax tree ) based on the given toke
tree *generateAST(list *token_list);

#endif
