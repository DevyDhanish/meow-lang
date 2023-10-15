#include "../include/map.hpp"
#include "../include/token.hpp"
#include <vector>
#include <iostream>

std::vector<struct node> global_variable_map;

void insert(Token _key, Token _value){

    for(node &i : global_variable_map){
        if(i.key == _key){
            i.value = _value;
            return;
        }
    }

    node newNode;
    newNode.key = _key,
    newNode.value = _value; 

    global_variable_map.push_back(newNode);
}


Token get(Token _key){
    for(node i : global_variable_map){
        if(i.key == _key) return i.value;
    }

    return makeToken(_TOKEN_EMPTY, "", "", 0, 0);
}

void show(){
    for(node i : global_variable_map){
        std::cout << i.key._TOKEN_VALUE << " " << i.value._TOKEN_VALUE << "\n";
    }
}