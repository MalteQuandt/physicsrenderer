// External Includes
// -----------------
#define GLFW_INCLUDE_NONE

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <imgui.h>
#include <imgui_impl_glfw.h>
#include <imgui_impl_opengl3.h>
// Self-Made Includes
// ------------------
// Callback methods for GLFW
#include "include/Callbacks.h"

// STD-Lib Includes
// ----------------
#include <iostream>
#include <windows.h>
#include <string>

// Symbolic Constants
// ------------------
#define WINDOW_HEIGHT 480
#define WINDOW_WIDTH 800

#define APPLICATION_NAME "Physics Renderer"

// Using Declarations
// ------------------
using namespace std;
using namespace phyren;


int main() {
    // Initialize the glfw context
    if (!glfwInit()) {
        cerr << "[ERROR] GLFW could not be initialized!" << endl;
        terminateContext();
        return -1;
    }

    // Set the window hints for the window creation
    // --------------------------------------------
    // Give GLFW the hint for the correct opengl version, in this case 4.0
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 0);
    // Make it known that only core profile methods should be used
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    // Create the window and it's associated context
    GLFWwindow *window{glfwCreateWindow(WINDOW_WIDTH, WINDOW_HEIGHT, APPLICATION_NAME, nullptr, nullptr)};

    // If the window has not been created:
    if (nullptr == window) {
        cerr << "[ERROR] Window could not be created!" << endl;
        terminateContext();
        return -1;
    }
    // Set the properties for the window as minimum height = window_height, min width = window_width
    // and no maximum for both
    glfwSetWindowSizeLimits(window, WINDOW_WIDTH, WINDOW_HEIGHT, GLFW_DONT_CARE, GLFW_DONT_CARE);
    glfwMaximizeWindow(window);
    // Register the callbacks
    // ----------------------
    glfwSetErrorCallback(error_callback);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
    // ----------------------

    // Make the opengl context of the window current for the calling thread
    glfwMakeContextCurrent(window);

    // Load all opengl function pointers
    if (!gladLoadGLLoader((GLADloadproc) glfwGetProcAddress)) {
        cerr << "[ERROR] Failed to initalize GLAD!" << endl;
        glfwDestroyWindow(window);
        terminateContext();
        return -1;
    }

    // Setup Dear ImGui context
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO &io = ImGui::GetIO();
    // Setup Platform/Renderer bindings
    ImGui_ImplGlfw_InitForOpenGL(window, 1);
    ImGui_ImplOpenGL3_Init("#version 400");
    // Setup Dear ImGui style
    ImGui::StyleColorsDark();

    // Make the buffer refresh with the color white and 100% opacity
    glClearColor(1.0f, 1.0f, 1.0f, 1.0f);

    clog << "[STATUS] The window was created!" << endl;

    // Main render loop
    while (!glfwWindowShouldClose(window)) {
        // Round-Robing Type Polling by calling the callback methods
        glfwPollEvents();
        // Clear the color and depth buffer
        glClear(GL_COLOR_BUFFER_BIT);

        // feed inputs to dear imgui, start new frame
        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();

        // render your GUI
        ImGui::ShowDemoWindow();

        // Render dear imgui into screen
        ImGui::Render();
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

        // Swap the front and back buffer
        glfwSwapBuffers(window);
    }
    // Get rid of the dearimgui context
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();

    // Dispose of the current window and it's bound context
    glfwDestroyWindow(window);
    terminateContext();

    clog << "[STATUS] Window and context were terminated!" << endl;
    return 0x0;
}
