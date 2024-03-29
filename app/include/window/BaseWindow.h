//
// Created by malte on 5/12/2022.
//

#pragma once

#include <window/WindowContext.h>

namespace phyren {
    /**
     * Class that is used to create and represent the most basic glfw window context
     */
    class BaseWindow final : public phyren::WindowContext {
    private:
        // Create this method from the factory.
        // Creation can fail, thus we call it here
        static std::shared_ptr<WindowContext> create(const unsigned int width, const unsigned int height, const std::string& name);

        explicit BaseWindow(GLFWwindow* window, unsigned int width, unsigned int height);

        friend class WindowFactory;
    };
}