cmake_minimum_required(VERSION 3.0)
project(MeowLang)

include_directories(include)

add_library(ll src/ll/ll.c)
add_library(core src/core/core.c)
add_executable(meow src/main.c)
target_link_libraries(meow core ll)