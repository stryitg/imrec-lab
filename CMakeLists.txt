cmake_minimum_required(VERSION 3.12)

project(lab1)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -Wall -DDEBUG")
set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_DEBUG} -Wall")

add_executable(lab1 "")
target_include_directories(lab1 PRIVATE "${CMAKE_CURRENT_SOURCE_DIR}/include")
target_sources(lab1 
    PRIVATE 
        ${CMAKE_CURRENT_SOURCE_DIR}/src/main.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/src/img.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/src/symbol.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/src/text_recognizer.cpp)
        
