cmake_minimum_required(VERSION 3.20)
project(lab2)

set(CMAKE_CXX_STANDARD 17)

add_executable(lab2
        main.cpp
        parser.h
        parser.cpp
        factories.h
        factories.cpp
        workers.h
        workers.cpp
        exceptions.h
        exceptions.cpp)
