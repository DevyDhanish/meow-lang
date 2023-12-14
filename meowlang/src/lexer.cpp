#include "../../include/lexer.hpp"
#include "../../include/token.hpp"
#include "../../include/core.hpp"
#include "../../include/error.hpp"

#include <string>
#include <vector>
#include <ctype.h>
#include <iostream>
#include <sstream>
#include <cstdint>

bool isdigitC(char w)
{
    return w >= '0' && w <= '9';
}

bool isdigitS(const std::string &word)
{
    for (char w : word)
    {
        if(!isdigitC(w)) return false;
    }

    return true;
}

bool isalphaC(char w)
{
    return (w >= 'a' && w <= 'z') || (w >= 'A' && w <= 'Z');
}

bool isTypeOfBracket(char w)
{
    if ( brackets.find(w) == brackets.end()) return false;
    else return true;
}

bool isStringS(const std::string &word)
{
    if(word[0] != '"' && word[word.size() - 1] != '"') return false;

    return true;
}

bool isFloat( const std::string &word ) {

    if(!isdigitC(word[0])) return false;    // if the first letter is not a digit then it is not a float

    for( char w : word)
    {
        if(w == '.') return true;
    }

    return false;
}

bool isInt( const std::string &word )
{
    for( char w : word )
    {
        if(!isdigitC(w)) return false;
    }

    return true;
}

// used to disassemble line into words for example line ` x = 5 + 5;` will be disassembled into `x,=,5,+,5,;`
// This method will be called for each line
std::vector<std::string> disassembleLine(meow_line line){

    std::vector<std::string> output;                                // each disassembled word will be pushed into this vector
    std::string curr_line = line.line;
    size_t curr_pos = 0;

    while(curr_pos < curr_line.size()){                             // loop until it reaches the end of the line
        char lookAhead = curr_line[curr_pos];

        if(lookAhead == ' ' || lookAhead == '\r' || lookAhead == '\t' || lookAhead == '\n'){                                       // ignore space
            curr_pos += 1;
        }

        else if(lookAhead == commentChar) // ignore comments when lexing but it does not work : (
        {
            while(1)
            {
                if(curr_pos > curr_line.size()) break;
                
                curr_pos += 1;
            }
        }

        else if(isdigitC(lookAhead))
        {
            std::string word;
            word += lookAhead;
            curr_pos += 1;

            while(1){
                if(curr_pos > curr_line.size()) break;
                if(!isdigit(curr_line[curr_pos]) && curr_line[curr_pos] != '.') break;
                word += curr_line[curr_pos];
                curr_pos += 1;
            }

            output.push_back(word);
        }

        else if(operator_pair.find(lookAhead) != operator_pair.end()){
            
            std::string word;
            word += lookAhead;
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

        // 34 = "
        // 39 = ' <- won't work
        else if (lookAhead == 34){    // if a string is detected surround it with `"` for example `this is a string` will become "this is a string"
            std::string word;
            word += '"';
            curr_pos += 1;
            while(1){
                if(curr_line[curr_pos] == 34) break;

                word += curr_line[curr_pos];

                if(curr_pos > curr_line.size()){
                    //displayError(_E_SYNTAX_ERROR, line.line, line.line_number);
                }

                curr_pos += 1;
            }
            word += '"';
            output.push_back(word);
            curr_pos += 1;
        }

        else if (isalphaC(lookAhead)){
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
            //displayError(_E_UNKNOW_TOKEN_ERROR, line.line, line.line_number);
        }

    }

    return output;
}

std::vector<std::string> preprocesor(std::vector<std::string> &words)
{
    std::vector<std::string> result;

    uint32_t counter = 0;
    std::string curword;

    while(counter < words.size())
    {
        curword = words[counter];
        if(curword == "+=")
        {
            std::string prevWord = words[counter - 1];
            result.push_back("=");
            result.push_back(prevWord);
            result.push_back("+");
        }
        else if(curword == "-=")
        {
            std::string prevWord = words[counter - 1];
            result.push_back("=");
            result.push_back(prevWord);
            result.push_back("-");
        }
        else if(curword == "*=")
        {
            std::string prevWord = words[counter - 1];
            result.push_back("=");
            result.push_back(prevWord);
            result.push_back("*");
        }
        else if(curword == "/=")
        {
            std::string prevWord = words[counter - 1];
            result.push_back("=");
            result.push_back(prevWord);
            result.push_back("/");
        }
        else if(curword == "%=")
        {
            std::string prevWord = words[counter - 1];
            result.push_back("=");
            result.push_back(prevWord);
            result.push_back("%");
        }
        else
        {
            result.push_back(words[counter]);
        }

        counter++;
    }

    return result;
}

// @brief the given vector of "meow_line" to a vector of respective tokens
std::vector<Token> Lexer::tokenize(meow_line _prog_lines){

    std::vector<Token> _prog_token_list;
    std::vector<std::string> words = disassembleLine(_prog_lines);
    std::vector<std::string> processed_words = preprocesor(words);
    for(std::string curr_word : processed_words){
        
        // current word is keyword or is present in the tokens map
        if(knowTokens.find(curr_word) != knowTokens.end()){
            _prog_token_list.push_back(makeToken(
                knowTokens[curr_word],
                curr_word,
                _prog_lines.line,
                _prog_lines.line_number
            ));
        }

        else if(isStringS(curr_word)){
            std::string word = "";

            for(int i = 1; i <= curr_word.size() - 2; i++)
            {
                word += curr_word[i];
            }

            _prog_token_list.push_back(makeToken(
                _TOKEN_STRING,
                word,
                _prog_lines.line,
                _prog_lines.line_number
            ));
        }

        else if(isFloat(curr_word))
        {
            _prog_token_list.push_back(
                makeToken(
                    _TOKEN_FLOAT,
                    curr_word,
                    _prog_lines.line,
                    _prog_lines.line_number
                )
            );
        }

        else if(isInt(curr_word))
        {
            _prog_token_list.push_back(
                makeToken(
                    _TOKEN_INT,
                    curr_word,
                    _prog_lines.line,
                    _prog_lines.line_number
                )
            );
        }
        
        // if current word is not present in the token map then it must a variable name
        else if(knowTokens.find(curr_word) == knowTokens.end()){
            _prog_token_list.push_back(makeToken(
                _TOKEN_VAR,
                curr_word,
                _prog_lines.line,
                _prog_lines.line_number
            ));
        }
        else{
            std::cout << "Error while lexing\n";
        }
    }
    
    return _prog_token_list;
}    