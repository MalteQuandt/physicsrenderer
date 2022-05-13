//
// Created by malte on 5/13/2022.
//

#ifndef PHYSICS_RENDERER_SHAREDSTATE_H
#define PHYSICS_RENDERER_SHAREDSTATE_H

#include "controller/InputController.h"
#include "render/OverlayRenderer.h"
#include "Camera.h"

#include <memory>

namespace phyren {
    /**
     * Wrapper struct for all the global state that the application needs.
     * @brief In order to work with glfw, one *needs* to use global variables (or use the user pointer provided, which is just globals with extra steps)
     *
     */
    struct SharedState {
        /**
        * Controller that takes all the input data form glfw
        */
        static std::shared_ptr<InputController> controller;
        /**
        * Handler for the overlay
        */
        static std::shared_ptr<OverlayRenderer> overlay;
        /**
        * Handler for the camera of the user
        */
        static std::shared_ptr<Camera> camera;
    };
}


#endif //PHYSICS_RENDERER_SHAREDSTATE_H
