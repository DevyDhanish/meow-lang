#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Datastructures
#include "../include/DS/list.h"
#include "../include/DS/dict.h"

// Libraries
#include "../include/core/core.h"
#include "../include/AST_GEN/ast_gen.h"
#include "../include/lexer/lexer.h"
//#include "../include/token/tokendef.h"

FILE *fileptr;
char *fileBuffer;

int main(int argc, char **argv){

    fileptr = fopen(argv[1], "r");

    // Read the file and put it in buffer
    fileBuffer = filetobuffer(fileptr);

    // List to store the tokens
    list *token_list = NULL;
    //addtoken();

    // Get each word from the buffer
    // And tokenize it
    token_list = tokenize(token_list, fileBuffer);

    if(token_list == NULL){
        printf("\nFailed to tokenize the contents\n");
        return 1;
    }

    //token_list = gettokenizedlist();
    displaydict(token_list);

    tree *ast = generateAST(token_list);

    freeTree(ast);

    //printf("%s", (char *)getvaluefromkey(dictlist, key));

    //freeList(token_list);

    // FILE *asmfile = fopen(argv[2], "w");

    // const char *tex1 = "section .text\n\nglobal _start\n_start:\n";
    // fputs(tex1, asmfile);

    // while (token_list != NULL && token_list->data != NULL) {
    //     dict *item = (dict *)token_list->data;

    //     if (strcmp(item->key, "__RETURN__") == 0) {
    //         const char *text2 = "\tmov rax, 60\n";
    //         fputs(text2, asmfile);
    //     }

    //     if(strcmp(item->key, "__INT__") == 0){
    //         char *text6 = "\tmov rdi, ";
    //         fputs(text6, asmfile);
    //         fputs((const char *)item->value, asmfile);
    //         fputs((const char *)"\n", asmfile);
    //     }

    //     if (strcmp(item->key, "__VAR__") == 0) {
    //         const char *text3 = "\tmov rdi, 4\n";
    //         fputs(text3, asmfile);
    //     }

    //     if(strcmp(item->key, "__NULL__") == 0){
    //         const char *text5 = "\tmov rdi, 0\n";
    //         fputs(text5, asmfile);
    //     }

    //     token_list = token_list->next;
    // }

    // const char *text = "\tsyscall";
    // fputs(text, asmfile);

    // fclose(asmfile);

    // printf("Meow lang Compiling.... Done\n");

    // list *l = NULL;

    // l = append(l, (char *)"first");
    // l = append(l, (char *)"second");
    // l = append(l, (char *)"third");

    // printf("front\n");
    // while(l->next != NULL){
    //     printf("%s,", (char *)l->data);
    //     l = l->next;
    // }

    // printf("%s,", (char *)l->data);

    // printf("\n");

    // printf("back\n");
    // while (l != NULL)
    // {
    //     printf("%s,", (char *)l->data);

    //     l = l->back;
    // }
    

    // free everthing
    freefilebuffer();
    freetokenlist();
    
    return 0;
}