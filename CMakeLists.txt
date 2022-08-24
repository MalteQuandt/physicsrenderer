# Set up the CMAKE Project and download all the dependencies
# Version: 2.0
# Author: Malte Quandt
cmake_minimum_required(VERSION 3.21)

project(physics_renderer
        VERSION 1.0
        DESCRIPTION "Physics Renderer Application Framework"
        LANGUAGES CXX)

#===Find required packages===
find_package(Python REQUIRED
        COMPONENTS
            Interpreter)
find_package(OpenGL REQUIRED)

# ======== Options =========
option(BUILD_TESTS "Should tests be generated?" ON)

# ======= Variables ========
set(CMAKE_CXX_STANDARD 20)

#====Internal-Libraries=====
add_subdirectory(lib)
if(BUILD_TESTS)
    enable_testing()
    add_subdirectory(test)
endif()
add_subdirectory(app)
