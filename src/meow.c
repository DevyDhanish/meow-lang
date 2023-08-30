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
#include "../include/token/tokendef.h"

FILE *fileptr;
char *fileBuffer;
FILE *asmfile;

void generator(tree *root){
    if (root->data == __RETURN__){
        const char *text0 = "section .data\n";
        fputs(text0, asmfile);
        const char *text1 = "hello db "; 
        fputs(text1, asmfile);
        fputs((const char *)root->childs[0]->data, asmfile);

        const char *nullT = ",0xa";
        fputs(nullT, asmfile);

        const char *text23 = "\nlen equ $ - hello\n";
        fputs(text23, asmfile);

        const char *text2 = "\nsection .text\n";
        fputs(text2, asmfile);

        const char *text3 = "global _start\n";
        fputs(text3, asmfile);

        const char *text4 = "_start:\n";
        fputs(text4, asmfile);

        const char *text5 = "\tmov rax, 4\n";
        fputs(text5, asmfile);

        const char *text6 = "\tmov rbx, 1\n";  
        fputs(text6, asmfile);      

        const char *text7 = "\tmov rcx, hello\n";  
        fputs(text7, asmfile);      

        const char *text8 = "\tmov rdx, len\n";   
        fputs(text8, asmfile);          

        const char *text9 = "\tint 0x80\n";    
        fputs(text9, asmfile);        

        const char *text10 = "\tmov rax, 1\n";
        fputs(text10, asmfile);           

        const char *text11 = "\txor rbx, rbx\n"; 
        fputs(text11, asmfile);          

        const char *text12 = "\tint 0x80\n";
        fputs(text12, asmfile);
    }

    for(int i = 0; i < root->child_size; i++){
        generator(root->childs[i]);
    }
}

int main(int argc, char **argv){

    if(argc < 1) return 0;

    fileptr = fopen(argv[1], "r");
    asmfile = fopen(argv[2], "w");

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
    //displaydict(token_list);

    tree *ast = generateAST(token_list);

    generator(ast);

    freeTree(ast);

    // system("nasm -f elf64 main.asm -o main.o");
    // system("ld main.o -o main");
    //system("ld main.o -o main");


    //printf("%s", (char *)getvaluefromkey(dictlist, key));

    //freeList(token_list);

    

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

    printf("Meow lang compiling done......\n");
    
    return 0;
}
