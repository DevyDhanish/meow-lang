#ifndef PARSER_H
#define PARSER_H

#include "../DS/tree.h"
#include "../DS/list.h"

tree *generateAST(list *token_list);

#endif