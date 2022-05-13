//
// Created by malte on 5/12/2022.
//

#ifndef PHYSICS_RENDERER_WINDOWFACTORY_H
#define PHYSICS_RENDERER_WINDOWFACTORY_H

#include "glad/glad.h"
#include "GLFW/glfw3.h"

#include "WindowContext.h"
#include "BaseWindow.h"

#include <memory>

namespace phyren {

    enum class WindowTypes : unsigned int {
        BASE_WINDOW
    };

#define STARTING_WINDOW_HEIGHT 480
#define STARTING_WINDOW_WIDTH 800

    class WindowFactory {
    public:
        /**
         * Create window context object from the given glfw window context
         *
         * @param window opaque glfw window object
         * @param type the type of the window context
         *
         * @return a shared pointer to the object
         */
        static std::shared_ptr<WindowContext>
        Create(WindowTypes type = WindowTypes::BASE_WINDOW, unsigned int width = STARTING_WINDOW_WIDTH,
               unsigned int height = STARTING_WINDOW_HEIGHT, const std::string &name = "application");
    };
}


#endif //PHYSICS_RENDERER_WINDOWFACTORY_H