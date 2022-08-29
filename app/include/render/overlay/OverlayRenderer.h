//
// Created by malte on 5/12/2022.
//

#pragma once

// GLFW/GLad includes
#include <glad/glad.h>
#include <GLFW/glfw3.h>
// Imgui includes
#include <imgui.h>
#include <backends/imgui_impl_glfw.h>
#include <backends/imgui_impl_opengl3.h>

// Self Written includes
#include <render/overlay/OverlayWindow.h>

// STD includes
#include <string>
#include <memory>

namespace phyren {
    namespace overlay {
        /**
         * Representation of the DearImGUi overlay in a class wrapper
         */
        class OverlayRenderer {
        public:
            /**
             * Create an instance of OverlayRenderer
             *
             * @param window the window for the context.
             * @param glslVersion the version of glsl that should be used.
             *
             * @return the renderer instance.
             */
            static std::shared_ptr<OverlayRenderer>
                instance(GLFWwindow *window, const std::string &glslVersion);

            /**
             * Render the overlay
             */
            virtual void render();

            /**
             * Setup the callbacks for the overlay
             */
            virtual void setupCallbacks(GLFWwindow *window);

            /**
             * Destroy the overlay renderer
             */
            virtual void destroy();

            /**
             * Register a new window for the overlay
             *
             * @param window the window to add to the registers
             */
            virtual void registerWindow(const OverlayWindow& window);
            /**
             * Register a new window for the overlay
             *
             * @param window the window to add to the registers
             */
            virtual void registerWindow(std::shared_ptr<OverlayWindow> window);

            /**
             * Remove a window that was registered
             *
             * @param window the window to remove from the registers
             */
            virtual void removeWindow(const OverlayWindow& window);

        private:
            // The windows that are being rendered in this context
            std::vector<OverlayWindow> windows;

            /**
             * Create the overlay renderer and set up the imgui context
             *
             * @param window the window for the context
             * @param glslVersion the version of glsl that should be used
             */
            OverlayRenderer(GLFWwindow *window, const std::string &glslVersion);
        };
    }
}