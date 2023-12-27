#pragma once

#include <string>
#include <cstdint>

enum MEOW_ERROR_TYPES
{
    SYNTAX_E,
    IDXOUTOFBOUNDS_E,
};


// msg part is optional, it's just there to provide recovery for example
// user : x ++= 10
// Meowlang : " Syntax error at line blah blah"
// Meowlang : " Did you mean += " <- these type of helpfull messages should be passes in the msg param
void Log(MEOW_ERROR_TYPES type, std::string msg, uint32_t line_number, std::string line);