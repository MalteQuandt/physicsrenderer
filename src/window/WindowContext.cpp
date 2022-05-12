//
// Created by malte on 5/12/2022.
//

#include "window/WindowContext.h"

using namespace std;
using namespace phyren;

WindowContext::WindowContext(GLFWwindow *window) : window(window) {}

shared_ptr<WindowContext> WindowContext::create() {
    return nullptr;
}

WindowContext::~WindowContext() {
    glfwDestroyWindow(this->window);
}

void WindowContext::makeCurrent() {
    // Make this window current
    glfwMakeContextCurrent(this->window);
}

GLFWwindow *WindowContext::getRaw() {
    return this->window;
}