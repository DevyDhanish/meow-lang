#include "../../include/color.hpp"
#include <iostream>
#include <windows.h>

void printColoredTextWIN(MEOW_COLORS color, std::string text)
{
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

    const int RED = FOREGROUND_RED;
    const int GREEN = FOREGROUND_GREEN;
    const int BLUE = FOREGROUND_BLUE;


    switch(color)
    {
        case MEOW_COLORS::M_RED:
        {
            SetConsoleTextAttribute(hConsole, RED),
            std::cout << text << "\n";
            break;
        }
        case MEOW_COLORS::M_BLUE:
        {
            SetConsoleTextAttribute(hConsole, BLUE),
            std::cout << text << "\n";
            break;
        }
        case MEOW_COLORS::M_GREEN:
        {
            SetConsoleTextAttribute(hConsole, GREEN),
            std::cout << text << "\n";
            break;
        }
    }

    SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
}

void printColoredText(MEOW_COLORS color, std::string text)
{
    printColoredTextWIN(color, text);
}