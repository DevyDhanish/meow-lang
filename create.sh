#!/bin/bash

make create_libs
make create_main
cd build/
./meowlang main.meow
cd ..
