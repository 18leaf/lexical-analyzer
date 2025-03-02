cmake_minimum_required(VERSION 3.29)
project(lexical_analyzer C)

set(CMAKE_C_STANDARD 23)

add_executable(lexical_analyzer src/main.c
        include/token.h
        src/token.c
        include/scanner.h
        src/scanner.c)


