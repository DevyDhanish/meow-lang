#pragma once

#include <string>
#include <vector>
#include "code.hpp"

/*
    a byteblock 
    will have 
        -id
        -block of bytecode
*/

class Block
{
public:
    std::string id;
    std::vector<bytecode> bytes;
    std::vector<Block *> block;

    Block(std::string i) : id(i) {}

    std::string getId()
    {
        return id;
    }

    std::vector<bytecode> getBytes()
    {
        return bytes;
    }

    Block* getBlockById(std::string qid)
    {
        if(id == qid)
        {
            return this;
        }

        for(Block *bb : block)
        {
            Block *foundBlock = bb->getBlockById(qid);
            if(foundBlock != nullptr) {
                return foundBlock; // Return the found object if not nullptr
            }
        }

        return nullptr; // Return nullptr if the block with qid isn't found in this branch
    }
};