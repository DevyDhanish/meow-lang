cmake_minimum_required(VERSION 3.0)
project(MeowLang)

include_directories(include)

add_library(core src/core/core.c)
add_library(DS src/DS/list.c)
add_library(lexer src/lexer/lexer.c)
add_executable(meow src/meow.c)
target_link_libraries(meow core DS lexer)
