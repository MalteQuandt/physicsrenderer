# Set up the CMAKE Project and download all the dependencies
# Version: 2.0
# Author: Malte Quandt
cmake_minimum_required(VERSION 3.21)

project(physics_renderer
        VERSION 1.0
        DESCRIPTION "Physics Renderer Framework"
        LANGUAGES CXX)

#===Find required packages===
find_package(Python REQUIRED
        COMPONENTS
            Interpreter)
find_package(OpenGL REQUIRED)

# ====== Git =======
find_package(Git QUIET)
if(GIT_FOUND AND EXISTS "${CMAKE_SOURCE_DIR}/.git")
    option(GIT_SUBMODULE "If submodules should be checked during configure" ON)
    if(GIT_SUBMODULE)
        message(STATUS "Update Submodules")
        execute_process(
                COMMAND ${GIT_EXECUTABLE} submodule update --init --recursive
                WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
                RESULT_VARIABLE GIT_SUBMOD_RESULT
        )
        if(NOT GIT_SUBMOD_RESULT EQUAL "0")
            message(FATAL_ERROR "git submodule update --init --recursive failed with ${GIT_SUBMOD_RESULT}!")
        endif()
    endif()
endif()

# ======== Options =========
option(BUILD_TESTS "Should tests be generated?" ON)
option(DEBUG_BUILD "If the Engine should be build in debug mode" OFF)

# ======= Variables ========
set(CMAKE_CXX_STANDARD      23)
set(OPENGL_VERSION_MAJOR    3)
set(OPENGL_VERSION_MINOR    3)
set(APPLICATION_NAME        ${CMAKE_PROJECT_NAME})

#====Internal-Libraries=====
add_subdirectory(lib)
if(BUILD_TESTS)
    enable_testing()
    add_subdirectory(test)
endif()
add_subdirectory(app)
