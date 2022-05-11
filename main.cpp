// External Includes
// -----------------
#define GLFW_INCLUDE_NONE

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <imgui.h>
#include <imgui_impl_glfw.h>
#include <imgui_impl_opengl3.h>

// STD-Lib Includes
// ----------------
#include <iostream>

// Self-Made Includes
// ------------------
// Callback methods for GLFW
#include "include/Callbacks.h"
#include "InputParser.h"
#include "utility.h"

// Symbolic Constants
// ------------------
#define STARTING_WINDOW_HEIGHT 480
#define STARTING_WINDOW_WIDTH 800

#define OPENGL_VERSION_MAJOR 3
#define OPENGL_VERSION_MINOR 3

#define STRINGIFY(x) #x
#define TOSTRING(X) STRINGIFY(X)
#define GLSL_VERSION TOSTRING(OPENGL_VERSION_MAJOR)TOSTRING(OPENGL_VERSION_MAJOR)"0"

#define APPLICATION_NAME "Physics Renderer"

// Using Declarations
// ------------------
using namespace std;
using namespace phyren;

int main(int argc, char **argv) {
    InputParser parser{argc, argv};
    // Parse zero-parameter arguments
    if (parser.exists("--help") || parser.exists("-h")) {
        // Display the help message and return
        cout << helpMessage() << endl;
        return 0x0;
    }
    // Iterate over the input token field to handle remaining arguments
    while (parser.hasElements()) {
        // Fetch the first element from the token list
        string front{parser.pop()};
        // Check the element and handle it
        if ("-i" == front) {} // set the integration method for the engine
        if ("-3D" == front) {} // enable 3d support
    }

    // Initialize the glfw context
    if (!glfwInit()) {
        cerr << "[ERROR] GLFW could not be initialized!" << endl;
        terminateContext();
        return -1;
    }
    // Give GLFW the hint for the correct opengl version
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, OPENGL_VERSION_MAJOR);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, OPENGL_VERSION_MINOR);
    // Make it known that only core profile methods should be used
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    // Create the window and it's associated context
    GLFWwindow *window{
            glfwCreateWindow(STARTING_WINDOW_WIDTH, STARTING_WINDOW_HEIGHT, APPLICATION_NAME, nullptr, nullptr)};
    if (nullptr == window) {
        cerr << "[ERROR] Window could not be created!" << endl;
        terminateContext();
        return -1;
    }
    // Set the properties with a minimum, but no maximum size
    glfwSetWindowSizeLimits(window, STARTING_WINDOW_WIDTH, STARTING_WINDOW_HEIGHT, GLFW_DONT_CARE, GLFW_DONT_CARE);
    glfwMaximizeWindow(window);
    // Register the callbacks for glfw
    // ----------------------
    glfwSetErrorCallback(error_callback);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
    // ----------------------
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
    // Setup Platform/Renderer bindings, and install imgui's internal callbacks
    ImGui_ImplGlfw_InitForOpenGL(window, 1);
    ImGui_ImplOpenGL3_Init("#version " GLSL_VERSION);
    // Setup Dear ImGui style
    ImGui::StyleColorsDark();

    // Make the buffer refresh with the color white and 100% opacity
    glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
    clog << "[STATUS] The window was created!" << endl;
    clog << "[STATUS] main game loop is starting..." << endl;

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
    clog << "[STATUS] Program will now terminate" << endl;
    return 0x0;
}
