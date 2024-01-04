#pragma once

#include <string>
#include <iostream>

enum MEOW_COLORS
{
    M_RED,
    M_GREEN,
    M_BLUE,
};

#ifdef __win32
#include <windows.h>
void printColoredTextWIN(MEOW_COLORS color, std::string text);
void printColoredText(MEOW_COLORS color, std::string text);
#else
void printColoredText(MEOW_COLORS color, std::string text)
{
    std::cout << "Not Implemented yet\n";
}
#endif