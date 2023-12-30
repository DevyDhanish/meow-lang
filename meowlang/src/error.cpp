#include "../../include/error.hpp"
#include "../../include/color.hpp"
#include <cstdint>
#include <iostream>
#include <unordered_map>

std::unordered_map<MEOW_ERROR_TYPES, std::string> error_msg
{
    {SYNTAX_E, "Syntax error"},
    {IDXOUTOFBOUNDS_E, "Index out of bounds"},
};

void Log(MEOW_ERROR_TYPES type, std::string msg, uint32_t line_number, std::string line)
{
    if(error_msg.find(type) == error_msg.end())
    {
        std::cout << "No provided error info found for error type " << type << "\n";
    }

    printColoredText(MEOW_COLORS::M_RED, "ERROR!!!");
    
    std::cout << error_msg[type] << "\n";
    std::cout << "occurred at line number : " << line_number << "\n";
    std::cout << "while executing the line : `" << line << "`\n";
    if(msg.size()) std::cout << msg  << "\n";
    exit(0); // exit the prog
}