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

bool phyren::loadGladPointers() {
    // Load all opengl function pointers
    if (!gladLoadGLLoader((GLADloadproc) glfwGetProcAddress)) {
        cerr << "[ERROR] Failed to initalize GLAD!" << endl;
        terminateContext();
        return false;
    }
    return true;
}
