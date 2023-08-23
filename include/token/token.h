#ifndef TOKEN_H
#define TOKEN_H


// Structure of a token
// each token will have a type which is a char array == string
// and a value pointer that can point to any value type
typedef struct token{
    char *type;
    void *value;
}token;

#endif