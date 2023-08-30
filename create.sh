#!/bin/bash

make create_libs
make create_main
cd build/
./meowlang ../example/main.meow ../example/main.asm
cd ..
