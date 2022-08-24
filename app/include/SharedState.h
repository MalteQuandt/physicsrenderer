//
// Created by malte on 5/13/2022.
//

#ifndef PHYSICS_RENDERER_SHAREDSTATE_H
#define PHYSICS_RENDERER_SHAREDSTATE_H

#include <controller/InputController.h>
#include <render/OverlayRenderer.h>
#include <render/camera/Camera.h>
#include <Constants.h>

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
        * Shared pointer to the camera so that the callbacks can access it
        */
        static std::shared_ptr<Camera> camera;
    };
}


#endif //PHYSICS_RENDERER_SHAREDSTATE_H
