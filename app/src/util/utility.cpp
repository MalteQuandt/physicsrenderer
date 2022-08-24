//
// Created by malte on 5/11/2022.
//

#include "util/utility.h"

#include <iostream>

using namespace phyren;
using namespace std;

std::string phyren::helpMessage() {
    // TODO: Write help message!
    return "HELP MESSAGE";
}

// Terminate the glfw context
void phyren::terminateContext() {
    glfwTerminate();
}