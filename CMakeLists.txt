cmake_minimum_required(VERSION 3.17)
project(lankfordP1V2)

set(CMAKE_CXX_STANDARD 14)

add_executable(lankfordP1
        Lexical_Analyzer.cpp
        Lexical_Analyzer.h
        Project1.cpp
        Set_Limits.cpp
        Set_Limits.h
        Syntactical_Analyzer.cpp
        Syntactical_Analyzer.h)
