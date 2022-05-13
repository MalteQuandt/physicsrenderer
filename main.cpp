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
#include "InputParser.h"
#include "util/utility.h"
#include "util/Callbacks.h"
#include "render/OverlayRenderer.h"
#include "window/WindowFactory.h"
#include "SharedState.h"

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
        if ("-i" == front) {

        } // set the integration method for the engine
        if ("-3D" == front) {

        } // enable 3d support
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

    // Set up the input controller instance, controller part of the MVC-Architecture
    SharedState::controller=InputController::instance();

    // Create the glfw window context
    std::shared_ptr<WindowContext> window{
            WindowFactory::Create(WindowTypes::BASE_WINDOW, STARTING_WINDOW_WIDTH, STARTING_WINDOW_HEIGHT,
                                  APPLICATION_NAME)};
    // Set the properties with a minimum, but no maximum size
    glfwSetWindowSizeLimits(window->getRaw(), STARTING_WINDOW_WIDTH, STARTING_WINDOW_HEIGHT, GLFW_DONT_CARE,
                            GLFW_DONT_CARE);
    glfwMaximizeWindow(window->getRaw());
    // Register the callbacks for this glfw window
    // ---------------------------------
    glfwSetErrorCallback(Callbacks::error_callback);
    glfwSetFramebufferSizeCallback(window->getRaw(), Callbacks::framebuffer_size_callback);
    glfwSetKeyCallback(window->getRaw(), Callbacks::key_callback);
    // ---------------------------------
    // Bind this window to the current context
    window->makeCurrent();

    // Do the glad setup
    if (!loadGladPointers()) { return -1; };

    // Make the buffer refresh with the color white and 100% opacity
    glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
    clog << "[STATUS] The window was created!" << endl;
    clog << "[STATUS] main game loop is starting..." << endl;

    SharedState::overlay = OverlayRenderer::instance(window->getRaw(), GLSL_VERSION);

    double t{0.0f};
    // Set the time each physics step simulates
    const double dt{0.01};
    // How much time is left to render
    double accumulator{0.0};
    // The current time of this system
    double prevTime{0.0f};

    // Main render loop
    while (!glfwWindowShouldClose(window->getRaw())) {
        // Calculate, how long the previous frame took:
        double currentTime{glfwGetTime()};
        double delta{currentTime - prevTime};
        prevTime = currentTime;

        // Make sure we don't do too much work
        if (delta > 0.25f) {
            delta = 0.25f;
        }
        // Set, how much time we now have to simulate
        accumulator += delta;

        // Round-Robing Type Polling by calling the callback functions
        glfwPollEvents();
        // Process the just-polled data
        SharedState::controller->process(delta);
        // Clear the color buffer
        glClear(GL_COLOR_BUFFER_BIT);

        // Decouple rendering from physics integration and introduce fixed time step
        while (accumulator >= dt) {

            // Set at what time in the simulation we are currently
            t += dt;
            // Set how many more seconds need to be rendered
            accumulator -= dt;
        }

        // Render overlay
        SharedState::overlay->render();
        // Swap the front and back buffer to make the just-rendered-to buffer visible
        glfwSwapBuffers(window->getRaw());
    }
    // Get rid of the dearimgui context
    SharedState::overlay->destroy();
    // Force destruction before `terminateContext()`.
    window.reset();
    // Destroy the glfw context
    terminateContext();

    clog << "[STATUS] Program will now terminate" << endl;
    return 0x0;
}
