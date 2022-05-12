//
// Created by malte on 5/12/2022.
//

#ifndef PHYSICS_RENDERER_BASEWINDOW_H
#define PHYSICS_RENDERER_BASEWINDOW_H

#include "WindowContext.h"

namespace phyren {
    /**
     * Class that is used to create and represent the most basic glfw window context
     */
    class BaseWindow final : public phyren::WindowContext {
    private:
        // Create this method from the factory.
        // Creation can fail, thus we call it here
        static std::shared_ptr<WindowContext> create(const unsigned int width, const unsigned int height, const std::string& name);
        explicit BaseWindow(GLFWwindow* window);
        friend class WindowFactory;
    };
}
#endif //PHYSICS_RENDERER_BASEWINDOW_H
