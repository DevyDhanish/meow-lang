#include "../../include/parser/parser.hpp"
#include "../../include/DS/tree.hpp"
#include "../../include/token/token.hpp"
#include "../../include/core/core.hpp"

#include <vector>

Tree _rt_Tree_parse(std::vector<Token> prog_tokens){
    Token startToken;
    startToken._TOKEN_TYPE = _TOKEN_START;
    startToken._TOKEN_LINE = "";
    startToken._TOKEN_VALUE = START_NODE;
    startToken._TOKEN_LINE_NUMBER = 0;

    Tree root(startToken);

    size_t lookAhead = 0;

    while(lookAhead < prog_tokens.size()){
        if(prog_tokens[lookAhead]._TOKEN_TYPE == _TOKEN_SHOW){
            root._rt_None_add_child(Tree(prog_tokens[lookAhead]));

            lookAhead += 1;
        }

        else if(prog_tokens[lookAhead]._TOKEN_TYPE == _TOKEN_PLUS){
            Tree add(prog_tokens[lookAhead]);
            add._rt_None_add_child(Tree(prog_tokens[lookAhead - 1]));
            add._rt_None_add_child(Tree(prog_tokens[lookAhead + 1]));

            root._rt_None_add_child(add);

            lookAhead += 2;
        }

        else{
            lookAhead += 1;
        }
    }
    return root;
}