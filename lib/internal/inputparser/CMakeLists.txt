project(inputparser
        VERSION 1.0
        DESCRIPTION "Parse console input"
        LANGUAGES CXX)

set(src ${CMAKE_CURRENT_SOURCE_DIR}/src/InputParser.cpp)

add_library(inputparser
        STATIC)
target_sources(inputparser
        PUBLIC
            ${src})
target_include_directories(inputparser
        PUBLIC
            include)