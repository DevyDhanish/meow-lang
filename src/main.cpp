#include <iostream>
#include <fstream>
#include <vector>

#include "../include/core/core.hpp"

using std::vector;
using std::cout;
using std::ifstream;
using std::string;


int main(int argc, char **argv){

    // if .meow file is not passed
    if(argc < 2){
        cout << "NO, input file" << "\n";
        return 0;
    }

    Core core;

    vector<string> _prog_lines = core.file_to_vect(argv[1]);

    for(string lines : _prog_lines){
        cout << lines;
    }
    
    return 0;
}