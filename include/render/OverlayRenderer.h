//
// Created by malte on 5/12/2022.
//

#ifndef PHYSICS_RENDERER_OVERLAYRENDERER_H
#define PHYSICS_RENDERER_OVERLAYRENDERER_H

#include "glad/glad.h"
#include "GLFW/glfw3.h"

#include "imgui.h"
#include "backends/imgui_impl_glfw.h"
#include "backends/imgui_impl_opengl3.h"

#include <string>
#include <memory>

namespace phyren {
    /**
     * Render class that represents the overlay created with the dearimgui library
     */
    class OverlayRenderer {
    public:
        /**
         * Create an instance of OverlayRenderer
         *
         * @param window the window for the context
         * @param glslVersion the version of glsl that should be used
         *
         * @return the renderer instance
         */
        static std::shared_ptr<OverlayRenderer> instance(GLFWwindow* window, const std::string& glslVersion);

        /**
         * Render the overlay
         */
        virtual void render();

        /**
         * Setup the callbacks for the overlay
         */
        virtual void setupCallbacks(GLFWwindow* window);

        /**
         * Destroy the overlay renderer
         */
        virtual void destroy();
    private:
        /**
         * Create the overlay renderer and set up the imgui context
         *
         * @param window the window for the context
         * @param glslVersion the version of glsl that should be used
         */
        OverlayRenderer(GLFWwindow *window, const std::string &glslVersion);
    };
}
#endif //PHYSICS_RENDERER_OVERLAYRENDERER_H
