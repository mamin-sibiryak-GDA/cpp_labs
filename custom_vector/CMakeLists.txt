cmake_minimum_required(VERSION 3.20)
project(lab1)

set(CMAKE_CXX_STANDARD 14)

add_subdirectory(lib/googletest)
include_directories(lib/googletest/googletest/include)
include_directories(lib/googletest/googlemock/include)

add_executable(lab1
        rna.cpp
        rna.h
        main.cpp
        nucl_ref.cpp)

target_link_libraries(lab1 gtest gtest_main)
