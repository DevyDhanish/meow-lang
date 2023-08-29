#include "../../include/AST_GEN/ast_gen.h"
#include "../../include/DS/list.h"
#include "../../include/DS/tree.h"
#include "../../include/DS/dict.h"
#include "../../include/token/tokendef.h"

// WHAT THE FUCK AM I DOING BRUH
tree *generateAST(list *token_list){
    tree *root = NULL;
    root = attach(root, __MAIN__);

    while (token_list->next != NULL)
    {
        dict *curr_item = (dict *) token_list->next->data;
        if(curr_item->key != __OPERATOR__){
            root = attach(root, curr_item->value);
        }
        else{
            dict *prev = (dict *) token_list->data;
            dict *nextnext = (dict *) token_list->next->next->data;

            tree *child1 = root->childs[0];
            child1 = attach(child1, prev->value);
            child1 = attach(child1, nextnext->value);

            token_list = nextnext;
        }

        token_list = token_list->next;

        break;
    }

    displayTree(root, 0);

    return root;
}