cmake_minimum_required(VERSION 3.17)
project(Pushdown_Automata)

set(CMAKE_CXX_STANDARD 14)

include_directories(include)

add_executable(Pushdown_Automata
        include/PDA.h
        src/PDA.cpp
        main.cpp)
