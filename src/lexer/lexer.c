#include "../../include/lexer/lexer.h"
#include "../../include/core/core.h"

#include "../../include/DS/list.h"
#include "../../include/DS/dict.h"

#include "../../include/token/tokendef.h"

#include <stdio.h>
#include <stdlib.h>

#define _EOL_CHAR ';'

char *line = NULL;
list *line_list = NULL;
char *word_buffer = NULL;

list *lines;
list *words;
list *token_list;

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

list *toLine(char *buffer){
    int start = 0;

    for(int j = 0; j < REDUSED_SIZE; j++){
        char ch = buffer[j];

        if(ch == _EOL_CHAR || ch == ':'){
            // append the line
            int line_lenght = j - start;

            for(int i = 0; i < line_lenght; i++){
                line[i] = buffer[start + i];
            }

            line[line_lenght] = ';';
            line = (char *) realloc(line, line_lenght + 1);
            line[line_lenght + 1] = '\0';

            line_list = append(line_list, line);

            start = j + 1;

            line = NULL;

            //continue;
        }
        else{
            line = (char *) realloc(line, j + 1);
        }
    }

    return line_list;
}

list *extractWords(list *lines){
    list *words_list = NULL;

    for(; lines != NULL; lines = lines->next){
        char *current_line = lines->data;
        
        // Split the lines into words and tokenise them
        //printf("current line - %s\n", current_line);

        int i = 0;
        int word_start = 0;
        int inside_quotes = 0;
        while(1){
            char ch = current_line[i];
            
            if(ch == '"') inside_quotes = !inside_quotes;

            if(ch == ' ' && !inside_quotes || ch == ';' && !inside_quotes){
                int word_lenght = i - word_start;
                
                if(word_lenght != 0){
                    word_buffer = (char *) malloc(word_lenght);

                    for(int j = 0; j < word_lenght; j++){
                        word_buffer[j] = current_line[word_start + j];
                    }

                    word_buffer[word_lenght] = '\0';

                    words_list = append(words_list, word_buffer);

                    word_buffer = NULL;

                    word_start = i + 1;
                }
            }

            if(ch == ';'){
                break;
            }

            i++;
        }
    }

    return words_list;
}

list *convertWordsToToken(list *words){

    list *token_list = NULL;
    for(; words != NULL; words = words->next){
        char *word = words->data;

        char *token = getvaluefromkey(_token_def_list, word);

        if(word[0] == ' ') continue;

        // check if string
        else if(word[0] == '"'){
            char *token = getvaluefromkey(_token_def_list, (char *)"str");
            token_list = append(token_list, creatitem(token, word));
        }

        // check if num
        else if(isNum(word)){
            char *token = getvaluefromkey(_token_def_list, (char *)"int");
            token_list = append(token_list, creatitem(token, word));
        }

        // if it is not a token then it is a variable
        else if(token == NULL){
            // if a token then append that token
            token_list = append(token_list, creatitem((char *)"var", word));
        }

        else{
            token_list = append(token_list, creatitem(token, word));
        }
    }

    return token_list;
}

list *tokenize(list *head, char *fileBuffer){

    if(_token_def_list == NULL){
        addtoken();
    }

    lines = toLine(fileBuffer);
    words = extractWords(lines);
    
    token_list = convertWordsToToken(words);

    return token_list;
}

void freetokenlist(){

    free(lines);
    free(words);

    free(token_list);

    free(line);
    free(word_buffer);

    freetokendeflist();
}