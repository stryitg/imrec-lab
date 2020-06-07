cmake_minimum_required(VERSION 3.10)
project(lab2)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

set(CMAKE_CXX_STANDARD 17)

SET(CMAKE_CXX_FLAGS  "${CMAKE_CXX_FLAGS} -ggdb")

add_executable(lab2 "")
target_include_directories(lab2 PRIVATE "${CMAKE_CURRENT_SOURCE_DIR}/include")
target_sources(lab2
    PRIVATE 
    "${CMAKE_CURRENT_SOURCE_DIR}/src/main.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/src/recognizer.cpp")
