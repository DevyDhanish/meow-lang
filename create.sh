#!/bin/bash

make create_lib
make create_bin
cd build
./meowlang ../exampleProg/main.meow
cd ..
