#include "../../include/parser/parser.h"
#include "../../include/DS/list.h"
#include "../../include/DS/tree.h"
#include "../../include/DS/dict.h"
#include "../../include/token/tokendef.h"

#include <string.h>

tree *generateAST(list *token_list)
{
    tree *root = NULL;

    root = attach(root, __MAIN__);

    displayTree(root, 0);

    return root;
}