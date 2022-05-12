//
// Created by malte on 5/12/2022.
//

#ifndef PHYSICS_RENDERER_OVERLAYRENDERER_H
#define PHYSICS_RENDERER_OVERLAYRENDERER_H

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <imgui.h>
#include <imgui_impl_glfw.h>
#include <imgui_impl_opengl3.h>

#include <string>

namespace phyren {
    /**
     * Render class that represents the overlay created with the dearimgui library
     */
    class OverlayRenderer {
    public:
        /**
         * Create the overlay renderer and set up the imgui context
         *
         * @param window the window for the context
         * @param glslVersion the version of glsl that should be used
         */
        OverlayRenderer(GLFWwindow* window, const std::string& glslVersion);
        /**
         * Render the overlay
         */
         void render();
        /**
         * Destroy the overlay renderer
         */
        void destroy();
    };
}


#endif //PHYSICS_RENDERER_OVERLAYRENDERER_H
