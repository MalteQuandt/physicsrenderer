//
// Definition of callback functions that are used in the main file of the applicaiton
// Created by malte on 5/4/2022.
//

#include "../include/Callbacks.h"





namespace phyren {
    // Called on glfw error to handle that error
    void error_callback(int error, const char *description) {
        fprintf(stderr, "%d:\nError: %s\n",error, description);
    }
    // Called on resize of the window/framebuffer
    void framebuffer_size_callback(__attribute__((unused))GLFWwindow* window, int width, int height) {
        glViewport(0,0, width, height);
    }
    // Terminate the glfw context
    void terminateContext() {
        glfwTerminate();
    }

}
