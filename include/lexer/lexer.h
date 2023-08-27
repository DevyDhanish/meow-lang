#ifndef LEXER_H
#define LEXER_H

#include <stdio.h>
#include "../DS/list.h"

// @brief tokenizes word according to the tokes defined in /include/token/tokendef.h
// @param buffer containing a the contents of the file
// @returns a list of dict with key as the token and values as the actual suppiled word example {(key : __RETURN__, value : return)}
list *tokenize(list *head, char *fileBuffer);

/*
@brief this actually frees the token list defied in the include/token/tokendef.h
becaues program gives error if I include both the lexer and tokedef in the meow.c file
*/
void freetokenlist();

#endif