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

#include "State.h"
#include "OverlayWindow.h"

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
             * @param window the window for the context
             * @param glslVersion the version of glsl that should be used
             * @param state the state of the current renderer
             *
             * @return the renderer instance
             */
            static std::shared_ptr<OverlayRenderer>
            instance(GLFWwindow *window, const std::string &glslVersion, State<3, float> &state);

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
            std::unique_ptr<State<3, float>> state;
            // The windows that are being rendered in this context
            std::vector<OverlayWindow> windows;

            /**
             * Create the overlay renderer and set up the imgui context
             *
             * @param window the window for the context
             * @param glslVersion the version of glsl that should be used
             * @param state the state of the system
             */
            OverlayRenderer(GLFWwindow *window, const std::string &glslVersion, State<3, float> &state);
        };
    }
}
#endif //PHYSICS_RENDERER_OVERLAYRENDERER_H
