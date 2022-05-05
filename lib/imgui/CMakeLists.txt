cmake_minimum_required(VERSION 3.21)
project(ImGui)

set(imgui_src
        # Top-Level files
        ${imgui_SOURCE_DIR}/imgui.cpp
        ${imgui_SOURCE_DIR}/imgui_demo.cpp
        ${imgui_SOURCE_DIR}/imgui_tables.cpp
        ${imgui_SOURCE_DIR}/imgui_widgets.cpp
        ${imgui_SOURCE_DIR}/imgui_draw.cpp

        # Backend-Specific code
        ${imgui_SOURCE_DIR}/backends/imgui_impl_glfw.cpp
        ${imgui_SOURCE_DIR}/backends/imgui_impl_opengl3.cpp)
set(imgui_inc
        # Top-Level Includes
        ${imgui_SOURCE_DIR}/
        # Backend-specific includes
        ${imgui_SOURCE_DIR}/backends/
        ${glfw_SOURCE_DIR}/include/
        )
add_library(imgui ${imgui_src})
include_directories(${imgui_inc})
target_include_directories(imgui PUBLIC ${imgui_inc})