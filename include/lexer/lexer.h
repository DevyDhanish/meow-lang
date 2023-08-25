#ifndef LEXER_H
#define LEXER_H

#include <stdio.h>
#include "../DS/list.h"

list *tokenize(list *head, char *buffer);

#endif