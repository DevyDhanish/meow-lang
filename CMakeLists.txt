cmake_minimum_required(VERSION 3.0)
project(MeowLang)

include_directories(include)

add_library(
    main src/core/core.c
    src/DS/list.c
    src/DS/dict.c
    src/lexer/lexer.c
)

# add_library(DS src/DS/list.c)
# add_library(lexer src/lexer/lexer.c)
add_executable(meow src/meow.c)
target_link_libraries(meow main)
