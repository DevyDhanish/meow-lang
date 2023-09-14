#pragma once

#include <vector>
#include <string>

#define START_NODE "__MAIN__"
#define END_NODE "__END__"

typedef struct _STRUCT_MEOW_LINE{
    std::string line;
    size_t line_number;
} meow_line;


std::vector<meow_line> file_to_vect(std::string);