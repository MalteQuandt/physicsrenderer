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
#include <vector>

// Self-Made Includes
// ------------------
// Callback methods for GLFW
#include "InputParser.h"
#include "util/utility.h"
#include "util/Callbacks.h"
#include "render/OverlayRenderer.h"
#include "window/WindowFactory.h"
#include "SharedState.h"
#include "render/Shader.h"
#include "render/ShaderProgram.h"
#include "Constants.h"

// Symbolic constants
// ------------------
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

// Function declarations
// ---------------------
void handleInput(shared_ptr<InputController>, shared_ptr<WindowContext>, shared_ptr<Camera>, float);

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
        // Set the integration method for the physics engine
        if ("-i" == front) {
            // TODO
            continue;
        }
        // If the engine should be started without a "head", meaning without the graphical component
        if ("-hl" == front || "--headless" == front) {
            // TODO
            continue;
        }
        // If the engine should record all the opengl data onto a video
        if ("-r" == front || "--record" == front) {
            // TODO
            continue;
        }
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

    // Create the glfw window context
    std::shared_ptr<WindowContext> window{
            WindowFactory::Create(WindowTypes::BASE_WINDOW, STARTING_WINDOW_WIDTH, STARTING_WINDOW_HEIGHT,
                                  APPLICATION_NAME)};
    // Set the properties with a minimum, but no maximum size
    glfwSetWindowSizeLimits(window->getRaw(), STARTING_WINDOW_WIDTH, STARTING_WINDOW_HEIGHT, GLFW_DONT_CARE,
                            GLFW_DONT_CARE);
    // glfwMaximizeWindow(window->getRaw());
    // Register the callbacks for this glfw window
    // ---------------------------------
    glfwSetErrorCallback(Callbacks::error_callback);
    glfwSetFramebufferSizeCallback(window->getRaw(), Callbacks::framebuffer_size_callback);
    glfwSetKeyCallback(window->getRaw(), Callbacks::key_callback);
    glfwSetScrollCallback(window->getRaw(), Callbacks::scroll_callback);
    glfwSetCursorPosCallback(window->getRaw(), Callbacks::mouse_movement_callback);
    // ---------------------------------
    // Bind this window to the current context
    window->makeCurrent();

    // Do the glad setup
    if (!gladLoadGLLoader((GLADloadproc) glfwGetProcAddress)) {
        cerr << "[ERROR] Failed to initalize GLAD!" << endl;
        terminateContext();
        return -0x1;
    }
    clog << "[STATUS] The window was created!" << endl;
    clog << "[STATUS] main game loop is starting..." << endl;

    // Setup the overlay renderer
    std::shared_ptr<OverlayRenderer> overlay{OverlayRenderer::instance(window->getRaw(), GLSL_VERSION)};

    // Generate vertex shader
    std::shared_ptr<Shader> vShader{Shader::Factory(
            "D:\\Desktop\\Fh_Daten\\Semester4\\PIC\\labor\\labor03\\physics-renderer\\shader\\simple_vertex_shader.vert",
            ShaderType::VERTEX_SHADER)};
    // Generate fragment shader
    std::shared_ptr<Shader> fShader{Shader::Factory(
            "D:\\Desktop\\Fh_Daten\\Semester4\\PIC\\labor\\labor03\\physics-renderer\\shader\\simple_fragment_shader.frag",
            ShaderType::FRAGMENT_SHADER)};
    // Generate the final shader program from the previously created shaders
    std::shared_ptr<ShaderProgram> shaderProgram{ShaderProgram::Factory(vShader, fShader)};

    // Generate the camera for the user in world space
    SharedState::camera = make_shared<Camera>(Camera(glm::vec3{0.0f, 0.0f, -3.0f}));

    // Set up the input controller instance, controller part of the MVC-Architecture
    SharedState::controller = InputController::instance();

    // TODO: Overhaul this into a vertex/model class and into another that
    //  can do the rendering of the world items
    float cubeVertices[] = {
            -0.5f, -0.5f, -0.5f,
            0.5f, -0.5f, -0.5f,
            0.5f, 0.5f, -0.5f,
            0.5f, 0.5f, -0.5f,
            -0.5f, 0.5f, -0.5f,
            -0.5f, -0.5f, -0.5f,

            -0.5f, -0.5f, 0.5f,
            0.5f, -0.5f, 0.5f,
            0.5f, 0.5f, 0.5f,
            0.5f, 0.5f, 0.5f,
            -0.5f, 0.5f, 0.5f,
            -0.5f, -0.5f, 0.5f,

            -0.5f, 0.5f, 0.5f,
            -0.5f, 0.5f, -0.5f,
            -0.5f, -0.5f, -0.5f,
            -0.5f, -0.5f, -0.5f,
            -0.5f, -0.5f, 0.5f,
            -0.5f, 0.5f, 0.5f,

            0.5f, 0.5f, 0.5f,
            0.5f, 0.5f, -0.5f,
            0.5f, -0.5f, -0.5f,
            0.5f, -0.5f, -0.5f,
            0.5f, -0.5f, 0.5f,
            0.5f, 0.5f, 0.5f,

            -0.5f, -0.5f, -0.5f,
            0.5f, -0.5f, -0.5f,
            0.5f, -0.5f, 0.5f,
            0.5f, -0.5f, 0.5f,
            -0.5f, -0.5f, 0.5f,
            -0.5f, -0.5f, -0.5f,

            -0.5f, 0.5f, -0.5f,
            0.5f, 0.5f, -0.5f,
            0.5f, 0.5f, 0.5f,
            0.5f, 0.5f, 0.5f,
            -0.5f, 0.5f, 0.5f,
            -0.5f, 0.5f, -0.5f,
    };
    // Position of the cube in world space
    glm::vec3 cubePos{0.0f, 0.0f, -5.0f};

    // Just for testing
    // ----------------
    unsigned int VBO, VAO;
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(cubeVertices), cubeVertices, GL_STATIC_DRAW);
    // position attribute
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void *) 0);
    glEnableVertexAttribArray(0);

    // Enable the depth buffer
    glEnable(GL_DEPTH_TEST);

    // Declare this shader program as the currently-active one
    shaderProgram->use();

    double t{0.0f};
    // Set the time each physics step simulates
    const double dt{0.01};
    // How much time is left to render
    double accumulator{0.0};
    // The current time of this system
    double prevTime{0.000001f};

    // Main render loop
    while (!glfwWindowShouldClose(window->getRaw())) {
        // ====== Frame Setup ======
        // -------------------------

        // Calculate, how long the previous frame took:
        double currentTime{glfwGetTime()};
        double delta{(currentTime - prevTime)};
        prevTime = currentTime;

        // Make sure we don't do too much work
        if (delta > 0.25f) {
            delta = 0.25f;
        }
        // Set, how much time we now have to simulate
        accumulator += delta;

        // === Process input data ===
        // --------------------------
        // Round-Robing Type Polling by calling the callback functions
        glfwPollEvents();
        // Handle the input of the user
        handleInput(SharedState::controller, window, SharedState::camera, delta);

        // Decouple rendering from physics integration and introduce fixed time step
        while (accumulator >= dt) {
            // Set at what time in the simulation we are currently
            t += dt;
            // Set how many more seconds need to be rendered
            accumulator -= dt;
        }

        // ======== Rendering ========
        // ---------------------------
        // Clear the color and depth buffer for the next frame of render
        glClearColor(1., 1., 1., 1.);
        glClear(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT);

        // Render world space
        // ------------------
        // Create the projection matrix
        glm::mat4 projection{glm::perspective(glm::radians(SharedState::camera->getZoom()),
                                              static_cast<float>(STARTING_WINDOW_WIDTH) /
                                              static_cast<float>(STARTING_WINDOW_HEIGHT), 0.1f, 100.0f)};
        // Set the shaderprogram to use
        shaderProgram->use();
        // Send the projection matrix to the gpu
        shaderProgram->setMat4("projection", projection);
        // Calculate the view transformation
        glm::mat4 view{SharedState::camera->getViewMatrix()};

        shaderProgram->setMat4("view", view);
        // Calculate the model matrix
        glm::mat4 model{glm::mat4{1.0f}};
        model = glm::translate(model, cubePos);
        shaderProgram->setMat4("model", model);

        glBindVertexArray(VAO);
        glDrawArrays(GL_TRIANGLES, 0, 36);

        // Render overlay
        // --------------
        overlay->render();

        // Swap the front and back buffer to make the just-rendered-to buffer visible
        glfwSwapBuffers(window->getRaw());
    }
    // Get rid of the dearimgui context
    overlay->destroy();
    // Force destruction before `terminateContext()`.
    window.reset();
    // Destroy the glfw context
    terminateContext();

    clog << "[STATUS] Program will now terminate" << endl;
    return 0x0;
}

/**
 * Handle the input that has occured over the last frame
 *
 * @param window the window context glfw currently runs
 * @param camera the camera of the
 */
void handleInput(shared_ptr<InputController> controller, shared_ptr<WindowContext> window, shared_ptr<Camera> camera,
                 float delta) {
    if (controller->isPressed(GLFW_KEY_W)) {
        camera->processMovement(Movement_Direction::FORWARD, delta);
    }
    if (controller->isPressed(GLFW_KEY_A)) {
        camera->processMovement(Movement_Direction::LEFT, delta);
    }
    if (controller->isPressed(GLFW_KEY_S)) {
        camera->processMovement(Movement_Direction::BACKWARD, delta);
    }
    if (controller->isPressed(GLFW_KEY_D)) {
        camera->processMovement(Movement_Direction::RIGHT, delta);
    }
    if (controller->isPressed(GLFW_KEY_SPACE)) {
        camera->processMovement(Movement_Direction::UP, delta);
    }
    if (controller->isPressed(GLFW_KEY_LEFT_SHIFT)) {
        camera->processMovement(Movement_Direction::DOWN, delta);
    }
    if (controller->isPressed(GLFW_KEY_ESCAPE) || controller->isPressed(GLFW_KEY_Q)) {
        glfwSetWindowShouldClose(
                window->getRaw(), GL_TRUE);
    }
    if (controller->isPressed(GLFW_KEY_2)) {
        // Enable the user to scroll through the world space:
        glfwSetInputMode(window->getRaw(), GLFW_CURSOR, GLFW_CURSOR_NORMAL);
        glfwSetCursorPosCallback(window->getRaw(), [](GLFWwindow *, double, double) {});
    }
    if (controller->isPressed(GLFW_KEY_F2)) {
        glfwSetInputMode(window->getRaw(), GLFW_CURSOR, GLFW_CURSOR_DISABLED);
        glfwSetCursorPosCallback(window->getRaw(), Callbacks::mouse_movement_callback);

    }
}
