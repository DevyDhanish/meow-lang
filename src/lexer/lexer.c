#include "../../include/lexer/lexer.h"
#include "../../include/core/core.h"

#include "../../include/DS/list.h"
#include "../../include/DS/dict.h"

#include "../../include/token/tokendef.h"

#include <stdio.h>
#include <stdlib.h>

#define _EOL_CHAR ';'
#define _DOUBLE_START_QUOTE '"'
#define _DOUBLE_END_QUOTE '"'

char *Wbuffer = NULL;
char *lineBuffer = NULL;

int lineLength;

int isNum(char *word){
    char *nums = "0123456789";

    for(int i = 0; i < 10; i++){
        if(nums[i] == word[0]){
            return 1;
        }
    }

    return 0;
}

char *getStrings(char *word, int line_length){
    char *wordbuffer = NULL;

    for(int i = 0; i <= line_length; i ++){
        if((char)word[i] == _DOUBLE_START_QUOTE){

            int wordLenght = (line_length - i) - 2;

            wordbuffer = (char *) malloc(wordLenght);

            for(int j = 0; j < wordLenght; j++){
                //if((char)word[i] == _DOUBLE_END_QUOTE) break;
                wordbuffer[j] = word[i + j + 1];
            }
            wordbuffer[wordLenght] = '\0';
            return wordbuffer;
        }
    }

    return NULL;
}

int isString(char *word, int wordLength){
    if((char)word[0] == _DOUBLE_START_QUOTE || (char)word[wordLength - 1] == _DOUBLE_END_QUOTE)return 1;

    return 0;
}

list *tokenize(list *head, char *fileBuffer){
    int lineStart = 0;

    if(_token_def_list == NULL){
        addtoken();
    }

    for(int i = 0; i < FILE_SIZE; i++){

        if((char)fileBuffer[i] == _EOL_CHAR){
            if(i > lineStart){
                lineLength = i - lineStart;
                lineBuffer = (char *)malloc(lineLength + 1);

                if(lineBuffer == NULL){
                    printf("Failed to malloc line buffer\n");
                    return NULL;
                }

                for(int j = 0; j < lineLength; j ++){
                    lineBuffer[j] = fileBuffer[lineStart + j];
                }

                lineBuffer[lineLength] = _EOL_CHAR;

                int wordStart = 0;
                int wordLenght = 0;
                // store any string that might be present in the line string can be identified is they start with " or '

                char *_string_present_in_line = getStrings(lineBuffer, lineLength);
                //printf("%s", _string_present_in_line);

                for (int k = 0; k <= lineLength; k++){
                    if((char)lineBuffer[k] == ' ' || (char)lineBuffer[k] == ';' || (char)lineBuffer[k] == '\n'){
                        if(k > wordStart){
                            wordLenght = k - wordStart;

                            Wbuffer = (char *)malloc(wordLenght);

                            if(Wbuffer == NULL){
                                printf("Failed to create Wbuffer\n");
                                return NULL;
                            }

                            for(int l = 0; l < wordLenght; l ++){
                                Wbuffer[l] = lineBuffer[wordStart + l];
                            }

                            if(isNum(Wbuffer)){
                                head = append(head, creatitem(getvaluefromkey(_token_def_list, (char *)"int"), Wbuffer));
                            }
                            else if(isString(Wbuffer, wordLenght) && _string_present_in_line != NULL){
                                //printf("adsfsadf");
                                head = append(head, creatitem(getvaluefromkey(_token_def_list, (char *)"str"), _string_present_in_line));
                                _string_present_in_line = NULL;
                            }
                            else if(isToken(Wbuffer)){
                                head = append(head, creatitem(getvaluefromkey(_token_def_list, Wbuffer), Wbuffer));
                            }
                            else if(!isToken(Wbuffer) && !isString(Wbuffer, wordLenght)){
                                head = append(head, creatitem(getvaluefromkey(_token_def_list, "var"), Wbuffer));
                            }

                            Wbuffer = NULL;
                        }

                        wordStart = k + 1;
                    }
                }

                lineBuffer = NULL;
            }

            lineStart = i + 1;
        }
    }

    return head;
}

void freetokenlist(){
    free(Wbuffer);
    free(lineBuffer);
    freetokendeflist();
}