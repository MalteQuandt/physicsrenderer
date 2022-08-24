project(Logger
        VERSION 1.0.0
        DESCRIPTION "Simple Logger Utility Library"
        LANGUAGES CXX)
set(src ${CMAKE_CURRENT_SOURCE_DIR}/src/Logger.cpp)

add_library(logger STATIC)

target_sources(logger
        PRIVATE
            ${src})
target_include_directories(logger
        PUBLIC
            include)