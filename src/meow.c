#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../include/DS/list.h"
#include "../include/DS/dict.h"

#include "../include/core/core.h"
#include "../include/lexer/lexer.h"
//#include "../include/token/tokendef.h"

FILE *fileptr;
char *fileBuffer;

void freeList(list *head) {
    while (head != NULL) {
        list *temp = head;
        head = head->next;
        free(temp->data); // Free the dict structure
        free(temp);       // Free the list node
    }
}

int main(int argc, char **argv){

    fileptr = fopen(argv[1], "r");

    // Read the file and put it in buffer
    fileBuffer = filetobuffer(fileptr);

    char *Wbuffer = NULL;
    int start = 0;

    list *token_list = NULL;
    //addtoken();

    // Get each word from the buffer
    // And tokenize it
    for (int i = 0; i <= FILE_SIZE; i++) {
        if (fileBuffer[i] == ' ' || fileBuffer[i] == ';' || fileBuffer[i] == '\n' || fileBuffer[i] == '\0') {
            if (i > start) {

                int wordLength = i - start;
                Wbuffer = (char *)malloc(wordLength + 1); // Allocate memory for the word
                
                if (Wbuffer == NULL) {
                    // Handle allocation failure
                    fprintf(stderr, "Memory allocation failed\n");
                    exit(1);
                }

                // Copy the characters from fileBuffer to Wbuffer
                for (int j = 0; j < wordLength; j++) {
                    Wbuffer[j] = fileBuffer[start + j];
                }
                Wbuffer[wordLength] = '\0';

                //token_list = append(token_list, creatitem(getvaluefromkey(_token_def_list, Wbuffer), Wbuffer));


                //break;

                // Tokenize
                token_list = tokenize(token_list, Wbuffer);

                //free(Wbuffer); // Free the allocated memory
                Wbuffer = NULL; // Reset Wbuffer to NULL
            }
            start = i + 1;
        }
    }

    //token_list = gettokenizedlist();
    displaydict(token_list);

    //printf("%s", (char *)getvaluefromkey(dictlist, key));

    //freeList(token_list);

    FILE *asmfile = fopen(argv[2], "w");

const char *tex1 = "section .text\n\nglobal _start\n_start:\n";
fputs(tex1, asmfile);

while (token_list != NULL && token_list->data != NULL) {
    dict *item = (dict *)token_list->data;

    if (strcmp(item->key, "__RETURN__") == 0) {
        const char *text2 = "\tmov rax, 60\n";

        // Write the text to the file
        fputs(text2, asmfile);
    }

    if (strcmp(item->key, "__VAR__") == 0) {
        const char *text3 = "\tmov rdi, 4\n";
        fputs(text3, asmfile);
    }

    if(strcmp(item->key, "__NULL__") == 0){
        const char *text5 = "\tmov rdi, 0\n";
        fputs(text5, asmfile);
    }

    token_list = token_list->next;
}

const char *text = "\tsyscall";
fputs(text, asmfile);

fclose(asmfile);

    printf("\n");

    return 0;
}