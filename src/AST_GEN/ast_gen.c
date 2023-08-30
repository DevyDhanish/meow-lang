#include "../../include/AST_GEN/ast_gen.h"
#include "../../include/DS/list.h"
#include "../../include/DS/tree.h"
#include "../../include/DS/dict.h"
#include "../../include/token/tokendef.h"


// WHAT THE FUCK AM I DOING BRUH
tree *generateAST(list *token_list){
    tree *root = NULL;

    root = attach(root, __MAIN__);

    while(token_list != NULL){

        dict *currentNode = (dict *)token_list->data;

        if(currentNode->key == __RETURN__){
            dict *nextNode = (dict *)token_list->next->data;

            root = attach(root, currentNode->key);
            if(nextNode != NULL){
                root->childs[0] = attach(root->childs[0], nextNode->value);

                token_list = token_list->next->next;
            }
        }
    }

    return root;
}