//
// Created by malte on 5/11/2022.
//

#ifndef PHYSICS_RENDERER_UTILITY_H
#define PHYSICS_RENDERER_UTILITY_H

#include "glad/glad.h"
#include "GLFW/glfw3.h"

#include <string>

/**
 * Utility functions that are too small or not focused enough to allow for their own source file
 */
namespace phyren {
    /**
     * create the help message that the user sees in the instance that the `-h` or `--help` console parameter was
     * supplied
     *
     * @return the help message
     */
    std::string helpMessage();
    /**
     * Method to call from glfw when an error occured
     *
     * @param error the error code
     * @param description a c-string description of the error
     */
    void error_callback(int error, const char *description);
    /**
    * Terminate the glfw context
    */
    void terminateContext();
}

#endif //PHYSICS_RENDERER_UTILITY_H
