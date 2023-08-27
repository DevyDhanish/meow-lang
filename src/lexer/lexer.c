#include "../../include/lexer/lexer.h"
#include "../../include/core/core.h"

#include "../../include/DS/list.h"
#include "../../include/DS/dict.h"

#include "../../include/token/tokendef.h"

#include <stdio.h>
#include <stdlib.h>

char *Wbuffer = NULL;

list *tokenize(list *head, char *fileBuffer){
    int start = 0;

    for (int i = 0; i <= FILE_SIZE; i++) {
        if (fileBuffer[i] == ' ' || fileBuffer[i] == '\n' || fileBuffer[i] == '\0') {
            if (i > start) {

                int wordLength = i - start;
                Wbuffer = (char *)malloc(wordLength + 1); // Allocate memory for the word
                
                if (Wbuffer == NULL) {
                    // Handle allocation failure
                    printf("Memory allocation failed\n");
                    return NULL;
                }

                // Copy the characters from fileBuffer to Wbuffer
                for (int j = 0; j < wordLength; j++) {
                    Wbuffer[j] = fileBuffer[start + j];
                }
                Wbuffer[wordLength] = '\0';                 // NULL terminate everyword

                //break;

                // Tokenize         // Tokenize it

                if(_token_def_list == NULL){
                //printf("Created the token list\n");
                    addtoken();
                }

                if(isNum(Wbuffer)){
                    head = append(head, creatitem(getvaluefromkey(_token_def_list, (char *)"int"), Wbuffer));
                }
                else if(!isToken(Wbuffer)){
                    head = append(head, creatitem(getvaluefromkey(_token_def_list, (char*)"var"), Wbuffer));
                }
                else if(isString(Wbuffer, &i)){
                    
                }
                else{
                    head = append(head, creatitem(getvaluefromkey(_token_def_list, Wbuffer), Wbuffer));
                }

                //free(Wbuffer); // Free the allocated memory
                Wbuffer = NULL; // Reset Wbuffer to NULL
            }

            start = i + 1;
        }
    }

    return head;
}

int isNum(char *word){
    char *nums = "0123456789";

    for(int i = 0; i < 10; i++){
        if(nums[i] == word[0]){
            return 1;
        }
    }

    return 0;
}

int isString(char *word, int *counter_i){

}

void freetokenlist(){
    free(Wbuffer);
    freetokendeflist();
}
