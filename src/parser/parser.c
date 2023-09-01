#include "../../include/parser/parser.h"
#include "../../include/DS/list.h"
#include "../../include/DS/tree.h"
#include "../../include/DS/dict.h"
#include "../../include/token/tokendef.h"

#include <string.h>


// tree *parser(list *tokens)
// {
//     tree *root = NULL;

//     root = attach(root, __MAIN__);

//     while (tokens != NULL)
//     {
//         dict *current_node_data = (dict *)tokens->data;
//         if(strcmp(current_node_data->key, __SHOW__) == 0){
//             root = attach(root, current_node_data->key);

//             dict *next_node_data = (dict *)tokens->next->data;
//             root->childs[root->child_size] = attach(root->childs[root->child_size], next_node_data->value);

//             tokens = tokens->next->next;
//         }

//         else if(strcmp(current_node_data->key, __OPERATOR__) == 0){
//             tree *ope = attach(root, current_node_data->value);

//             dict *next_node_data = (dict *) tokens->next->data;
//             dict *prev_node_data = (dict *) tokens->back->data;

//             if(strcmp((char *) current_node_data->value, "+") == 0){
//                 //int ans = (int)next_node_data->value + (int)prev_node_data->value;
//                 ope->childs[ope->child_size] = attach(ope->childs[ope->child_size], next_node_data->value);
//                 ope->childs[ope->child_size] = attach(ope->childs[ope->child_size], prev_node_data->value);
//             }

//             else if(strcmp((char *) current_node_data->value, "-") == 0){
//                 //int ans = (int)next_node_data->value - (int)prev_node_data->value;
//                 ope->childs[ope->child_size] = attach(ope->childs[ope->child_size], next_node_data->value);
//                 ope->childs[ope->child_size] = attach(ope->childs[ope->child_size], prev_node_data->value);
//             }

//             else if(strcmp((char *) current_node_data->value, "*") == 0){
//                 //int ans = (int)next_node_data->value * (int)prev_node_data->value;
//                 ope->childs[ope->child_size] = attach(ope->childs[ope->child_size], next_node_data->value);
//                 ope->childs[ope->child_size] = attach(ope->childs[ope->child_size], prev_node_data->value);
//             }

//             else if(strcmp((char *) current_node_data->value, "/") == 0){
//                 //int ans = (int)next_node_data->value / (int)prev_node_data->value;
//                 ope->childs[ope->child_size] = attach(ope->childs[ope->child_size], next_node_data->value);
//                 ope->childs[ope->child_size] = attach(ope->childs[ope->child_size], prev_node_data->value);
//             }

//             tokens = tokens->next;
//         }

//         else{
//             tokens = tokens->next;
//         }
//     }
    

//     return root;
// }

tree *parser(list *tokens) {
    tree *root = NULL;

    root = attach(root, __MAIN__);

    while (tokens != NULL) {
        dict *current_node_data = (dict *)tokens->data;

        if (strcmp(current_node_data->key, __SHOW__) == 0) {
            tree *showNode = attach(root, current_node_data->key);

            dict *next_node_data = (dict *)tokens->next->data;
            tree *valueNode = attach(showNode, next_node_data->value);

            tokens = tokens->next->next;
        }
        
        //else if (strcmp(current_node_data->key, __OPERATOR__) == 0) {
        //     tree *operatorNode = attach(root, current_node_data->value);

        //     dict *next_node_data = (dict *)tokens->next->data;
        //     dict *prev_node_data = (dict *)tokens->back->data;

        //     root = attach(operatorNode, next_node_data->value);
        //     root = attach(operatorNode, prev_node_data->value);

        //     tokens = tokens->next;
        // }

        //tokens = tokens->next;
    }

    return root;
}

// WHAT THE FUCK AM I DOING BRUH
tree *generateAST(list *token_list)
{
    tree *parsed_tree = parser(token_list);

    return parsed_tree;
}