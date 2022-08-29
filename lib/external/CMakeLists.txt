# Fetch external content
include(FetchContent)

# Fetch DearImGui into _deps
# --------------------------
FetchContent_Declare(imgui
        GIT_REPOSITORY https://github.com/ocornut/imgui.git
        )
FetchContent_MakeAvailable(imgui)
if (imgui_POPULATED)
    message(STATUS "${Green}ImGui should be downloaded! ${ColourReset}")
endif ()

# ==========GLFW==========
FetchContent_Declare(glfw
        GIT_REPOSITORY https://github.com/glfw/glfw.git
        )
if (NOT glfw_POPULATED)
    FetchContent_Populate(glfw)
    # Importent GLFW cmake flags
    set(GLFW_BUILD_DOCS OFF CACHE BOOL "" FORCE)
    set(GLFW_BUILD_TESTS OFF CACHE BOOL "" FORCE)
    set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)

    add_subdirectory(
            ${glfw_SOURCE_DIR}
            ${glfw_BINARY_DIR})
endif ()
message(STATUS "${Green}GLFW should be downloaded! ${ColourReset}")

# =========Glad==========
FetchContent_Declare(extern_glad
        GIT_REPOSITORY https://github.com/Dav1dde/glad.git
        )
FetchContent_GetProperties(extern_glad)
if (NOT extern_glad_POPULATED)
    FetchContent_Populate(extern_glad)
    # Set the glad options
    # you can select the appropriate options from this page:
    # https://glad.dav1d.de/
    # and then search through the glad-cmake file to find the right commands to set here:
    set(GLAD_PROFILE "core")
    set(GLAD_API "gl=${OPENGL_VERSION_MAJOR}.${OPENGL_VERSION_MINOR}")
    set(GLAD_INSTALL ON)

    add_subdirectory(
            ${extern_glad_SOURCE_DIR}
            ${extern_glad_BINARY_DIR}
            EXCLUDE_FROM_ALL
    )
endif ()
message(STATUS "${Green}GLAD should be downloaded and configured! ${ColourReset}")

# ========GLM=========
FetchContent_Declare(extern_glm
        GIT_REPOSITORY https://github.com/g-truc/glm.git
        )
FetchContent_GetProperties(extern_glm)
if (NOT extern_glm_POPULATED)
    FetchContent_Populate(extern_glm)
    add_subdirectory(
            ${extern_glm_SOURCE_DIR}
            ${extern_glm_BINARY_DIR}
    )
endif ()
message(STATUS "${Green}GLM should be downloaded! ${ColourReset}")

#=======STB-Lib============
FetchContent_Declare(extern_stb
        GIT_REPOSITORY https://github.com/nothings/stb.git
        )
FetchContent_MakeAvailable(extern_stb)
add_library(stb INTERFACE)
target_include_directories(stb
        INTERFACE
            ${extern_stb_SOURCE_DIR}
        )
if (extern_stb_POPULATED)
    message(STATUS "${Green}STB should be downloaded! ${ColourReset}")
endif ()

#==========ASSIMP===========
FetchContent_Declare(extern_assimp
        GIT_REPOSITORY https://github.com/assimp/assimp.git
        )
FetchContent_GetProperties(extern_assimp)
if (NOT extern_assimp_POPULATED)
    FetchContent_Populate(extern_assimp)

    if(DEBUG_BUILD)
        set(BUILD_SHARED_LIBS ON)
        message(STATUS "Build ASSIMP as a Dynamic Lib")
    else()
        message(STATUS "Build Assimp as a Static Lib")
        set(ASSIMP_INJECT_DEBUG_POSTFIX OFF)
    endif()
    set(ASSIMP_BUILD_ALL_EXPORTERS_BY_DEFAULT OFF)

    set(ASSIMP_WARNINGS_AS_ERRORS OFF)
    set(ASSIMP_BUILD_ASSIMP_TOOLS OFF)
    set(ASSIMP_BUILD_TESTS OFF)

    add_subdirectory(
            ${extern_assimp_SOURCE_DIR}
            ${extern_assimp_BINARY_DIR})

    message(STATUS "${Green}ASSIMP should be downloaded! ${ColourReset}")
else ()
    message(FATAL_ERROR "${Red} ASSIMP could not be properly prepared!${ColourReset}")
endif ()

# Set up the imgui library
# -------------------------------
add_library(imgui
        STATIC
        )
target_sources(imgui
        PUBLIC
            # Top-Level files
            ${imgui_SOURCE_DIR}/imgui.cpp
            ${imgui_SOURCE_DIR}/imgui_demo.cpp
            ${imgui_SOURCE_DIR}/imgui_tables.cpp
            ${imgui_SOURCE_DIR}/imgui_widgets.cpp
            ${imgui_SOURCE_DIR}/imgui_draw.cpp

            # Backend-Specific code
            ${imgui_SOURCE_DIR}/backends/imgui_impl_glfw.cpp
            ${imgui_SOURCE_DIR}/backends/imgui_impl_opengl3.cpp)

target_link_libraries(imgui
        PUBLIC
            glad
            glfw)

target_include_directories(imgui
        PUBLIC
            # Top-Level Includes
            ${imgui_SOURCE_DIR}/
            # Backend-specific includes
            ${imgui_SOURCE_DIR}/backends/
        )

# ======= Git-Submodules ========
add_subdirectory(catch2/source)
add_subdirectory(doctest/source)
add_subdirectory(google_test/source)
add_subdirectory(mpg/source)
#add_subdirectory(openal-soft/source)
