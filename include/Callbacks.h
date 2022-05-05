//
// Created by malte on 5/4/2022.
//

#ifndef PHYSICS_RENDERER_CALLBACKS_H
#define PHYSICS_RENDERER_CALLBACKS_H

#include <iostream>

// Need to be included in this order, so here we go
#include <glad/glad.h>
#include <GLFW/glfw3.h>

// Collection of callback methods for the main application
namespace phyren {
    void error_callback(int, const char *);
    void framebuffer_size_callback(GLFWwindow*, int, int);
    void terminateContext();
}

#endif //PHYSICS_RENDERER_CALLBACKS_H
