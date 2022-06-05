# Set up the CMAKE Project and download all the dependencies
# Version: 1.0
# Author: Malte Quandt

cmake_minimum_required(VERSION 3.21)
project(physics_renderer)
set(CMAKE_CXX_STANDARD 20)


# Fetch external content
include(FetchContent)
# Fetch DearImGui into _deps
# --------------------------
FetchContent_Declare(imgui
        GIT_REPOSITORY https://github.com/ocornut/imgui.git
)
FetchContent_MakeAvailable(imgui)
if(imgui_POPULATED)
    message(STATUS "${Green}ImGui should be downloaded! ${ColourReset}")
endif()

# Fetch GLFW into _deps
# ---------------------
FetchContent_Declare(glfw
        GIT_REPOSITORY https://github.com/glfw/glfw.git
)
if(NOT glfw_POPULATED)
    FetchContent_Populate(glfw)
    # Importent GLFW cmake flags
    set(GLFW_BUILD_DOCS OFF CACHE BOOL "" FORCE)
    set(GLFW_BUILD_TESTS OFF CACHE BOOL "" FORCE)
    set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)
    add_subdirectory(${glfw_SOURCE_DIR} ${glfw_BINARY_DIR})
endif()
message(STATUS "${Green}GLFW should be downloaded! ${ColourReset}")

# Fetch Glad into _deps
# ---------------------
FetchContent_Declare(extern_glad
        GIT_REPOSITORY https://github.com/Dav1dde/glad.git
)
FetchContent_GetProperties(extern_glad)
if(NOT extern_glad_POPULATED)
    FetchContent_Populate(extern_glad)
    # Set the glad options
    # you can select the appropriate options from this page:
    # https://glad.dav1d.de/
    # and then search through the glad-cmake file to find the right commands to set here:
    set(GLAD_PROFILE "core")
    set(GLAD_API "gl=3.3")
    set(GLAD_INSTALL ON)
    add_subdirectory(
            ${extern_glad_SOURCE_DIR}
            ${extern_glad_BINARY_DIR}
            EXCLUDE_FROM_ALL
    )
endif()
message(STATUS "${Green}GLAD should be downloaded and configured! ${ColourReset}")

# Fetch GLM into _deps
# --------------------
FetchContent_Declare(extern_glm
        GIT_REPOSITORY https://github.com/g-truc/glm.git
        )
FetchContent_GetProperties(extern_glm)
if(NOT extern_glm_POPULATED)
    FetchContent_Populate(extern_glm)
    add_subdirectory(
            ${extern_glm_SOURCE_DIR}
            ${extern_glm_BINARY_DIR}
    )
endif()
message(STATUS "${Green}GLM should be downloaded! ${ColourReset}")

#=======STB-Lib============
FetchContent_Declare(extern_stb
        GIT_REPOSITORY https://github.com/nothings/stb.git
        )
FetchContent_MakeAvailable(extern_stb)
add_library(stb INTERFACE)
include_directories(${extern_stb_SOURCE_DIR})
target_include_directories(stb INTERFACE ${extern_stb_SOURCE_DIR})
if(extern_stb_POPULATED)
    message(STATUS "${Green}STB should be downloaded! ${ColourReset}")
endif()

# Set up the imgui library
# -------------------------------
set(imgui_src
        # Top-Level files
        ${imgui_SOURCE_DIR}/imgui.cpp
        ${imgui_SOURCE_DIR}/imgui_demo.cpp
        ${imgui_SOURCE_DIR}/imgui_tables.cpp
        ${imgui_SOURCE_DIR}/imgui_widgets.cpp
        ${imgui_SOURCE_DIR}/imgui_draw.cpp

        # Backend-Specific code
        ${imgui_SOURCE_DIR}/backends/imgui_impl_glfw.cpp
        ${imgui_SOURCE_DIR}/backends/imgui_impl_opengl3.cpp lib/logger/src/Logger.cpp lib/logger/include/Logger.h)
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

#==========ASSIMP===========
FetchContent_Declare(extern_assimp
        GIT_REPOSITORY https://github.com/assimp/assimp.git
        )
FetchContent_GetProperties(extern_assimp)
if(NOT extern_assimp_POPULATED)
    FetchContent_Populate(extern_assimp)

    set(ASSIMP_WARNINGS_AS_ERRORS OFF)
    set(ASSIMP_BUILD_ASSIMP_TOOLS OFF)

    add_subdirectory(
            ${extern_assimp_SOURCE_DIR}
            ${extern_assimp_BINARY_DIR}
    )
endif()
message(STATUS "${Green}ASSIMP should be downloaded! ${ColourReset}")

#======Self-Written=========
include_directories(include) #${imgui_inc}

#====Internal-Libraries=====
add_subdirectory(lib)
# Set up all the source files
set(phyren_src
        # Main Folder Sources
        main.cpp
        # Source-Folder Sources
        src/controller/InputController.cpp
        src/InputParser.cpp
        src/util/FileHandler.cpp
        src/util/utility.cpp
        src/util/Callbacks.cpp
        src/render/ShaderProgram.cpp
        src/render/Shader.cpp
        src/render/OverlayRenderer.cpp
        src/camera/Camera.cpp
        src/window/WindowContext.cpp
        src/window/WindowFactory.cpp
        src/window/BaseWindow.cpp
        src/SharedState.cpp
        src/render/Mesh.cpp
        src/Texture.cpp
        src/Vertex.cpp
        src/StbImageSource.cpp
        src/camera/Camera3D.cpp
        src/render/Model.cpp
        src/render/ModelLoader.cpp
        )
# Create the executable
add_executable(physics_renderer ${phyren_src} )
# Link the executable to the external libraries
target_link_libraries(physics_renderer glad glfw imgui logger glm stb assimp)