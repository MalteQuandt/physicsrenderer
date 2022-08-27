//
// Created by malte on 5/12/2022.
//

#include <window/BaseWindow.h>
#include <Logger.h>


#include <iostream>

using namespace std;
using namespace phyren;
using namespace logging;

std::shared_ptr<WindowContext> BaseWindow::create(const unsigned int width, const unsigned int height, const std::string& name) {
    // Create the window and it's associated context
    GLFWwindow *window{
            glfwCreateWindow(static_cast<unsigned int>(width), static_cast<unsigned int>(height), name.c_str(), nullptr, nullptr)};
    if (nullptr == window) {
        Logger::GetLogger()->LogMessage("[ERROR] Window could not be created!"
                                                 , true, "Error");
        return nullptr;
    }
    shared_ptr<WindowContext> tmp{make_shared<WindowContext>(BaseWindow(window, width, height))};
    // Set up the window pointer
    glfwSetWindowUserPointer(window, tmp.get());
    // Setup callbacks
    // ---------------
    tmp->setupResizeCallback();
    return tmp;
}
// Create simple window object
BaseWindow::BaseWindow(GLFWwindow* window, unsigned int width, unsigned int height) : phyren::WindowContext(window, width, height) {}