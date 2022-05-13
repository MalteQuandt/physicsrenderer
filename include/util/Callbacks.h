//
// Created by malte on 5/4/2022.
//

#ifndef PHYSICS_RENDERER_CALLBACKS_H
#define PHYSICS_RENDERER_CALLBACKS_H

// Need to be included in this order, so here we go
#include "glad/glad.h"
#include "GLFW/glfw3.h"

#include <iostream>

// Collection of callback methods for the main application
namespace phyren {
    class Callbacks {
    public:
        /**
         * Callback method for glfw that is invoked when glfw encounters an error
         */
        static void error_callback(int, const char *);

        /**
         * Callback for the change in window size so that the viewport size can be
         * adapted
         *
         * @param window the glfw window
         */
        static void framebuffer_size_callback(GLFWwindow *,int,int);

        /**
         * Callback for actions that regard keys in glfw
         */
        static void key_callback(GLFWwindow *,int,int,int,int);
    };
}

#endif //PHYSICS_RENDERER_CALLBACKS_H
