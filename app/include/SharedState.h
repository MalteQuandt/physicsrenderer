//
// Created by malte on 5/13/2022.
//
#pragma once

#include <controller/InputController.h>
#include <render/camera/Camera.h>

#include <memory>

namespace phyren {
    /**
     * Wrapper struct for all the global state that the application needs.
     * @brief In order to work with glfw, one *needs* to use global variables (or use the user pointer provided, which is just globals with extra steps)
     */
    struct SharedState {
        /**
        * Controller that takes all the input data form glfw
        */
        static std::shared_ptr<InputController> controller;
        /**
        * Shared pointer to the camera into the world space so that the glfw-callbacks can access it
        */
        static std::shared_ptr<Camera> camera;
    };
}