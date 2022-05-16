//
// Definition of callback functions that are used in the main file of the applicaiton
// Created by malte on 5/4/2022.
//

#include "util/Callbacks.h"
#include "SharedState.h"

#include <iostream>

namespace phyren {

    // Called on glfw error to handle that error
    void Callbacks::error_callback(int error, const char *description) {
        fprintf(stderr, "%d:\nError: %s\n", error, description);
    }

    // Called on resize of the window/framebuffer
    void Callbacks::framebuffer_size_callback(__attribute__((unused))GLFWwindow *window, int width, int height) {
        glViewport(0, 0, width, height);
    }

    void Callbacks::key_callback(GLFWwindow *window, int key, int scancode, int action, int mods) {
        // Reflect the action on the key-map that was performed by the user
        switch (action) {
            case GLFW_RELEASE:
                std::clog << "[NOTIFY] The key " << static_cast<char>(key) << " was released!" << std::endl;
                SharedState::controller->released(key);
                return;
            case GLFW_PRESS:
                std::clog << "[NOTIFY] The key " << static_cast<char>(key) << " was pressed!" << std::endl;
                SharedState::controller->press(key);
                return;
            case GLFW_REPEAT:
                std::clog << "The key " << static_cast<char>(key) << " is currently being repeated!" << std::endl;
                // No further action is required, as we handle being held down ourselfs in the input controller module
                return;
            default:
                std::clog
                        << "[ERROR] An action on a key was performed, but it could not be asserted what that action was!"
                        << std::endl;
                // Nothing to do here, for now
                return;
        }
    }

    void Callbacks::scroll_callback(GLFWwindow *window, double xoffset, double yoffset) {
        SharedState::camera->processMouseScroll(yoffset);
    }

    void Callbacks::mouse_movement_callback(GLFWwindow *window, double xoffset, double yoffset) {
        if (firstMouse) {
            X = xoffset;
            Y = yoffset;
            firstMouse = false;
        }
        float xoff{static_cast<float>(xoffset - X)}; // left-to-right
        float yoff{static_cast<float>(Y - yoffset)}; // bottom-to-top

        X = xoffset;
        Y = yoffset;
        if (SharedState::camera->isEnabled(phyren::Enabled_Operations_Camera::MOUSE_MOVEMENT)) {
            SharedState::camera->processMouseMovement(xoff, yoff);
        }
    }

    bool Callbacks::firstMouse{true};
    // Set those values to the middle of the screen
    float Callbacks::X{STARTING_WINDOW_WIDTH / 2};
    float Callbacks::Y{STARTING_WINDOW_HEIGHT / 2};
}
