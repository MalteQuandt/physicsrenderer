configure_file(${CMAKE_CURRENT_SOURCE_DIR}/include/cmake/Configuration.hpp.in
        ${CMAKE_CURRENT_SOURCE_DIR}/include/cmake/Configuration.hpp @ONLY)

# Create the executable
add_executable(physics_renderer)

target_sources(physics_renderer
        PUBLIC
            # Main Application source
            ${CMAKE_CURRENT_SOURCE_DIR}/main.cpp
            # Source-Folder Sources
            # Input Controller
            ${CMAKE_CURRENT_SOURCE_DIR}/src/controller/InputController.cpp
            # Engine Pieces
        ${CMAKE_CURRENT_SOURCE_DIR}/src/engine/Entity3.cpp
            ${CMAKE_CURRENT_SOURCE_DIR}/src/engine/Transform.cpp
            # Render
            ${CMAKE_CURRENT_SOURCE_DIR}/src/render/ShaderProgram.cpp
            ${CMAKE_CURRENT_SOURCE_DIR}/src/render/Shader.cpp
            ${CMAKE_CURRENT_SOURCE_DIR}/src/render/OverlayRenderer.cpp
            ${CMAKE_CURRENT_SOURCE_DIR}/src/render/camera/Camera.cpp
            ${CMAKE_CURRENT_SOURCE_DIR}/src/render/camera/Camera3D.cpp
            ${CMAKE_CURRENT_SOURCE_DIR}/src/render/Model.cpp
            ${CMAKE_CURRENT_SOURCE_DIR}/src/render/ModelLoader.cpp
            ${CMAKE_CURRENT_SOURCE_DIR}/src/render/Line.cpp
            ${CMAKE_CURRENT_SOURCE_DIR}/src/render/OverlayWindow.cpp
            ${CMAKE_CURRENT_SOURCE_DIR}/src/render/Mesh.cpp
            ${CMAKE_CURRENT_SOURCE_DIR}/src/render/Texture.cpp
            ${CMAKE_CURRENT_SOURCE_DIR}/src/render/Vertex.cpp
            # Utils
            ${CMAKE_CURRENT_SOURCE_DIR}/src/util/FileHandler.cpp
            ${CMAKE_CURRENT_SOURCE_DIR}/src/util/utility.cpp
            ${CMAKE_CURRENT_SOURCE_DIR}/src/util/Callbacks.cpp
            # Windowing
            ${CMAKE_CURRENT_SOURCE_DIR}/src/window/WindowContext.cpp
            ${CMAKE_CURRENT_SOURCE_DIR}/src/window/WindowFactory.cpp
            ${CMAKE_CURRENT_SOURCE_DIR}/src/window/BaseWindow.cpp
            # Loose source folder
            ${CMAKE_CURRENT_SOURCE_DIR}/src/SharedState.cpp
            ${CMAKE_CURRENT_SOURCE_DIR}/src/StbImageSource.cpp
        )

target_include_directories(physics_renderer
        PUBLIC
            ${CMAKE_CURRENT_SOURCE_DIR}/include)

# Link the executable to the external libraries
target_link_libraries(physics_renderer
        PUBLIC
            glad
            glfw
            imgui
            logger
            glm
            stb
            assimp
            inputparser
            ${OPENGL_LIBRARIES})