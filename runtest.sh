#!/bin/bash

build/meowlang  test/bltins.meow
echo "test 1 passed"

build/meowlang  test/essential.meow 
echo "test 2 passed"

build/meowlang  test/idxasstest.meow
echo "test 3 passed"

build/meowlang  test/idxtest.meow 
echo "test 4 passed"

build/meowlang  test/input.meow
echo "test 5 passed"

build/meowlang  test/main.meow
echo "test 6 passed" 

build/meowlang  test/main2.meow
echo "test 7 passed" 

build/meowlang  test/nveen.meow
echo "test 8 passed" 

build/meowlang  test/prime.meow
echo "test 9 passed"

build/meowlang  test/recursion.meow
echo "test 10 passed" 

build/meowlang  test/return.meow
echo "test 11 passed"

build/meowlang  test/test.meow 
echo "test 12 passed"

build/meowlang  test/sorting.meow
echo "test 13 passed"

build/meowlang  test/forloop.meow
echo "test 14 passed"

build/meowlang  test/something.meow
echo "test 15 passed"


echo "All test passed"
