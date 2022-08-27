//
// Created by malte on 5/12/2022.
//

#include <window/WindowContext.h>

using namespace std;
using namespace phyren;

WindowContext::WindowContext(GLFWwindow *window, unsigned int width, unsigned int height) : window(window), width(width), height(height) {}

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
WindowContext::WindowContext(WindowContext&& wc) noexcept {
    swap(this->window, wc.window);
    swap(this->height, wc.height);
    swap(this->width, wc.width);
    swap(this->maximized, wc.maximized);
}
WindowContext& WindowContext::operator=(WindowContext&& wc) noexcept {
    if(this != &wc) {
        swap(this->window, wc.window);
        swap(this->height, wc.height);
        swap(this->width, wc.width);
        swap(this->maximized, wc.maximized);
    }
    return *this;
}

unsigned int WindowContext::getWidth() {
    return this->width;
}

unsigned int WindowContext::getHeight() {
    return this->height;
}

bool WindowContext::isMaximized() {
    return this->maximized;
}

void WindowContext::setWidth(unsigned int width) {
    this->width=width;
}
void WindowContext::setHeight(unsigned int height) {
    this->width=width;
}

// Callbacks:
// ----------
// Called on resize of the window/framebuffer
void WindowContext::framebuffer_size_callback(GLFWwindow *window, int width, int height) {
    // Return the window pointer
    WindowContext* context{static_cast<WindowContext*>(glfwGetWindowUserPointer(window))};
    // Call the actual callback
    context->framebuffer_size_callback_internal(window, width, height);
}

void WindowContext::framebuffer_size_callback_internal(__attribute__((unused))GLFWwindow *window, int width, int height) {
    setDimensions(width, height);
    glViewport(0, 0, width, height);
}

void WindowContext::setDimensions(unsigned int width, unsigned int height) {
    this->width=width;
    this->height=height;
}

void WindowContext::setupResizeCallback() {
    glfwSetFramebufferSizeCallback(this->window, WindowContext::framebuffer_size_callback);
}