#include "../include/lexer.hpp"
#include "../include/token.hpp"
#include "../include/core.hpp"
#include "../include/error.hpp"

#include <string>
#include <vector>
#include <ctype.h>
#include <iostream>


int LINE_IDENTATION = 0;

int isString(std::string word){
    if(word[0] == '"' && word[word.size() - 1] == '"') return 1;

    else return 0;
}

int isTypeOfBracket(char _bra){
    if(brackets.find(_bra) != brackets.end()) return 1;

    else return 0;
}

// used to disassemble line into words for example line ` x = 5 + 5;` will be disassembled into `x,=,5,+,5,;`
// This method will be called for each line
std::vector<std::string> disassembleLine(meow_line line){

    std::vector<std::string> output;                                // each disassembled word will be pushed into this vector
    std::string curr_line = line.line;
    size_t curr_pos = 0;

    for(char i : curr_line){
        if(i != ' ') break;
        else LINE_IDENTATION += 1;
    }

    while(curr_pos < curr_line.size()){                             // loop until it reaches the end of the line
        char lookAhead = curr_line[curr_pos];

        if(lookAhead == ' '){                                       // ignore space
            curr_pos += 1;
        }


        else if(operator_pair.find(lookAhead) != operator_pair.end()){

            curr_pos += 1;

            if(curr_line[curr_pos] == '='){
                output.push_back(operator_pair[lookAhead]);
                curr_pos += 1;
            }
            else
                output.push_back(std::string(1, lookAhead));

            //curr_pos += 1;
        }

        else if(isTypeOfBracket(lookAhead)){
            output.push_back(std::string(1, lookAhead));
            curr_pos += 1;
        }

        else if (lookAhead == '"'){                                 // if a string is detected surround it with `"` for example `this is a string` will become "this is a string"
            std::string word;
            word += '"';
            curr_pos += 1;
            while(curr_line[curr_pos] != '"'){
                word += curr_line[curr_pos];
                curr_pos += 1;

                if(curr_pos > curr_line.size()){
                    displayError(_E_SYNTAX_ERROR, line.line, line.line_number);
                }
            }
            word += '"';
            output.push_back(word);
            curr_pos += 1;
        }

        else if (isdigit(lookAhead)){
            std::string word;
            while(curr_pos < curr_line.size() && isdigit(curr_line[curr_pos])){
                word += curr_line[curr_pos];
                curr_pos += 1;
            }

            if(word != "")
                output.push_back(word);
                
            else output.push_back(std::string(1,lookAhead));
        }

        else if (isalpha(lookAhead)){
            std::string word;
            while(curr_pos < curr_line.size() && isalpha(curr_line[curr_pos])){
                word += curr_line[curr_pos];
                curr_pos += 1;
            }

            if(word != "")
                output.push_back(word);
            else output.push_back(std::string(1,lookAhead));
        }

        else{
            displayError(_E_UNKNOW_TOKEN_ERROR, line.line, line.line_number);
        }

    }

    return output;
}

// @brief the given vector of "meow_line" to a vector of respective tokens
std::vector<Token> Lexer::tokenize(meow_line _prog_lines){

    std::vector<Token> _prog_token_list;
    LINE_IDENTATION = 0;
    std::vector<std::string> words = disassembleLine(_prog_lines);

    for(std::string curr_word : words){
        
        if(knowTokens.find(curr_word) != knowTokens.end()){
            _prog_token_list.push_back(makeToken(
                knowTokens[curr_word],
                curr_word,
                _prog_lines.line,
                _prog_lines.line_number,
                LINE_IDENTATION
            ));
        }

        else if(isString(curr_word)){
            _prog_token_list.push_back(makeToken(
                _TOKEN_STRING,
                curr_word,
                _prog_lines.line,
                _prog_lines.line_number,
                LINE_IDENTATION
            ));
        }

        else if(isdigit(curr_word[0])){
            _prog_token_list.push_back(makeToken(
                _TOKEN_INT,
                curr_word,
                _prog_lines.line,
                _prog_lines.line_number,
                LINE_IDENTATION
            ));
        }

        else if(knowTokens.find(curr_word) == knowTokens.end()){
            _prog_token_list.push_back(makeToken(
                _TOKEN_VAR,
                curr_word,
                _prog_lines.line,
                _prog_lines.line_number,
                LINE_IDENTATION
            ));
        }
        else{
            displayError(_E_UNKNOW_TOKEN_ERROR, _prog_lines.line, _prog_lines.line_number);
        }
    }

    return _prog_token_list;
}    