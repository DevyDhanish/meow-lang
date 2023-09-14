#!/bin/bash

make Lib
make Bin
cd build
./meowlang ../exampleProg/main.meow
cd ..
