// External Includes
// -----------------
#define GLFW_INCLUDE_NONE

#include <glad/glad.h>
#include <GLFW/glfw3.h>

// STD-Lib Includes
// ----------------
#include <iostream>
#include <vector>

// Self-Made Includes
// ------------------
// CMake Generated
#include <cmake/Configuration.hpp>
// Utility
#include <util/utility.h>
#include <util/Callbacks.h>
// Windowing
#include <window/WindowFactory.h>
// Rendering
#include <render/OverlayRenderer.h>
#include <render/Shader.h>
#include <render/ShaderProgram.h>
#include <render/object/Sphere.tpp>
#include <render/State.h>
#include <render/object/Cube.tpp>
#include <render/object/Field.tpp>
#include <render/object/GeneralModel.tpp>
#include <render/camera/Camera3D.h>

#include <Constants.h>
#include <SharedState.h>
// Libraries
#include <Logger.h>
#include <InputParser.h>

// Symbolic constants
// ------------------
#define OPENGL_VERSION_MAJOR CMAKE_OPENGL_VERSION_MAJOR
#define OPENGL_VERSION_MINOR CMAKE_OPENGL_VERSION_MINOR


// Manage the version of opengl used here
#define STRINGIFY(x) #x
#define TOSTRING(X) STRINGIFY(X)
#define GLSL_VERSION TOSTRING(OPENGL_VERSION_MAJOR)TOSTRING(OPENGL_VERSION_MAJOR)"0"

// Using Declarations
// ------------------
using namespace std;
using namespace phyren;
using namespace overlay;
using namespace logging;

// Function declarations
// ---------------------
void handleInput(const shared_ptr<InputController> &controller,
                 const shared_ptr<WindowContext> &window,
                 const shared_ptr<Camera> &camera,
                 const std::shared_ptr<OverlayRenderer> &overlay,
                 float delta);
void setupCallbacks(const shared_ptr<WindowContext> &window);
void setupWindows(State<3, float>& state, const shared_ptr<OverlayRenderer>& overlay);

int main(int argc, char **argv) {
    // If only edges should be drawn
    bool lines{false};
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
        string front{move(parser.pop())};
        // Check the element and handle it
        // Set the integration method for the physics engine
        if ("-i" == front) {
            // TODO
            continue;
        }
        if ("-l" == front || "--lines" == front) {
            lines = true;
            continue;
        }
        if ("-nl" == front || "--noLogging" == front) {
            Logger::disable();
        }
    }

    // Initialize the glfw context
    if (not glfwInit()) {
        Logger::GetLogger()->LogMessage("GLFW could not be initialized!", true, "Error");
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
    setupCallbacks(window);
    // ---------------------------------
    // Bind this window to the current context
    window->makeCurrent();

    // Do the glad setup
    if (not gladLoadGLLoader((GLADloadproc) glfwGetProcAddress)) {
        Logger::GetLogger()->LogMessage("Failed to initialize GLAD!", true, "Error");
        terminateContext();
        return -0x1;
    }

    // Set the state of the application
    State<3, float> state{};
    Logger::GetLogger()->LogMessage("The window was created!", true, "Status");

    // Setup the overlay renderer
    std::shared_ptr<OverlayRenderer> overlay{OverlayRenderer::instance(window->getRaw(), GLSL_VERSION, state)};
    setupWindows(state, std::shared_ptr<OverlayRenderer>(overlay));

    // Generate vertex shader
    std::shared_ptr<Shader> vShader{Shader::Factory(
            R"(..\..\shader\simple_vertex_shader.vert)",
            ShaderType::VERTEX_SHADER)};
    // Generate fragment shader
    std::shared_ptr<Shader> fShader{Shader::Factory(
            R"(..\..\shader\simple_fragment_shader.frag)",
            ShaderType::FRAGMENT_SHADER)};
    // Generate the final shader program from the previously created shaders
    std::shared_ptr<ShaderProgram> shaderProgram{ShaderProgram::Factory(vShader, fShader)};

    // Generate the camera for the user in world space
    SharedState::camera = shared_ptr<Camera>(new Camera3D(glm::vec3{0.0f, 0.0f, -3.0f}));

    // Set up the input controller instance, controller part of the MVC-Architecture
    SharedState::controller = InputController::instance();

    // Load the models
    std::shared_ptr<object::Sphere<3, float>> sphereModel{make_shared<object::Sphere<3, float>>(object::Sphere<3, float>())};

    // Position of the cube in world space
    std::vector<glm::vec3> cubePos{
            glm::vec3{0, 0, -5},
            glm::vec3{2, 0, -5}
    };
    // Enable the depth buffer
    glEnable(GL_DEPTH_TEST);

    // Declare this shader program as the currently-active one
    shaderProgram->use();

    // Render the polygon lines
    if (lines) glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    Logger::GetLogger()->LogMessage("main game loop is starting...", true, "Status");

    double t{0.0f};
    // Set the time each physics step simulates
    const double dt{0.01};
    // How much time is left to render
    double accumulator{0.0};
    // The current time of this system
    double prevTime{0.000001f};

    // Main render loop
    while (not glfwWindowShouldClose(window->getRaw())) {
        // ====== Frame Setup ======
        // -------------------------

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

        // === Process input data ===
        // --------------------------
        // Round-Robing Type Polling by calling the callback functions
        glfwPollEvents();

        // Handle the input of the user
        handleInput(SharedState::controller, window, SharedState::camera, overlay, static_cast<float>(delta));

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
                                              static_cast<float>(window->getWidth()) /
                                              static_cast<float>(window->getHeight()), 0.1f, 100.0f)};
        // Set the shader program to use
        shaderProgram->use();

        // Send the projection matrix to the gpu
        shaderProgram->set("projection", projection);
        // Calculate the view transformation
        glm::mat4 view{SharedState::camera->getViewMatrix()};
        // Calculate the model matrix
        glm::mat4 model{};
        for (const auto &cube: cubePos) {
            shaderProgram->set("view", view);
            model = glm::mat4{1.0f};
            // First translate
            model = glm::translate(model, cube);
            // Then scale
            // model = glm::scale(model, glm::vec3{1.f, 1.f, 1.f});
            shaderProgram->set("model", model);
            // Render without using the index buffer, as we did not define that one right now
            // MAKE SURE THE SHADER IS IN USE BEFORE CALLING
            sphereModel->draw(shaderProgram);
        }

        // Render the stateful objects
        for(auto & obj : state.getObjects()) {
            model = glm::mat4{1.0f};
            model = glm::translate(model, obj->getPosition());
            model = glm::scale(model, obj->getScale());
            shaderProgram->set("model", model);
            obj->draw(shaderProgram);
        }
        model = glm::translate(model, glm::vec3{0,0,-5});
        shaderProgram->use();

        // Render overlay
        // --------------
        overlay->render();

        // Swap the front and back buffer to make the just-rendered-to buffer visible
        glfwSwapBuffers(window->getRaw());
    }
    // Get rid of the DearImGui context
    overlay->destroy();
    // Force destruction before `terminateContext()`.
    window.reset();
    // Destroy the glfw context
    terminateContext();
    Logger::GetLogger()->LogMessage("Program will now terminate", true, "Status");
    return 0x0;
}

/**
 * Handle the input that has occurred over the last frame
 *
 * @param window the window context glfw currently runs
 * @param camera the camera into the world space
 */
void handleInput(const shared_ptr<InputController> &controller, const shared_ptr<WindowContext> &window,
                 const shared_ptr<Camera> &camera,
                 const std::shared_ptr<OverlayRenderer> &overlay,
                 const float delta) {
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
        glfwSetWindowShouldClose(window->getRaw(), GL_TRUE);
    }
    if (controller->isPressed(GLFW_KEY_F1)) {
        // Enable the user to scroll through the world space:
        camera->disable(Enabled_Operations_Camera::MOUSE_MOVEMENT);
        glfwSetInputMode(window->getRaw(), GLFW_CURSOR, GLFW_CURSOR_NORMAL);
    }
    if (controller->isPressed(GLFW_KEY_F2)) {
        camera->enable(Enabled_Operations_Camera::MOUSE_MOVEMENT);
        glfwSetInputMode(window->getRaw(), GLFW_CURSOR, GLFW_CURSOR_DISABLED);
        // Reset the callbacks:
    }
    if (controller->isPressed(GLFW_KEY_F11)) {
        glfwMaximizeWindow(window->getRaw());
    }
}

/**
 * Setup the callbacks that for the given window
 *
 * @param window the window to set the callbacks for
 */
void setupCallbacks(const shared_ptr<WindowContext> &window) {
    glfwSetKeyCallback(window->getRaw(), Callbacks::key_callback);
    glfwSetScrollCallback(window->getRaw(), Callbacks::scroll_callback);
    glfwSetCursorPosCallback(window->getRaw(), Callbacks::mouse_movement_callback);
}


void setupWindows(State<3, float>& state, const shared_ptr<OverlayRenderer>& overlay) {
    overlay->registerWindow(OverlayWindow{state, [](OverlayWindow& w){
        static float x{3}, y{0}, z{-5};
        static float scale{1};

        ImGui::SliderFloat("X-axis", &x, -10, 10);
        ImGui::SliderFloat("Y-axis", &y, -10, 10);
        ImGui::SliderFloat("Z-axis", &z, -10, 10);
        ImGui::SliderFloat("Scale", &scale, 0.01, 100);

        if(ImGui::Button("Create Cube")) {
            shared_ptr<object::Cube<3, float>> tmp{new object::Cube<3, float>{}};
            tmp->setScale(glm::vec<3, float>(scale, scale, scale));
            tmp->setPosition(glm::vec3{x, y, z});
            w.getState().addObject(tmp);
        }

        if(ImGui::Button("Create Sphere")) {
            shared_ptr<object::Sphere<3, float>> tmp{new object::Sphere<3, float>{}};
            tmp->setScale(glm::vec<3, float>(scale, scale, scale));
            tmp->setPosition(glm::vec3{x, y, z});
            w.getState().addObject(tmp);
        }
        if(ImGui::Button("Create Field")) {
            shared_ptr<object::Field<3, float>> tmp{new object::Field<3, float>{10}};
            tmp->setScale(glm::vec<3, float>(scale, scale, scale));
            tmp->setPosition(glm::vec3{x, y, z});
            w.getState().addObject(tmp);
        }
        if(ImGui::Button("Create Model")) {
            shared_ptr<object::GeneralModel<3, float>> tmp{new object::GeneralModel<3, float>{R"(..\..\assets\models\backpack\backpack.obj)"}};
            tmp->setScale(glm::vec<3, float>(scale, scale, scale));
            tmp->setPosition(glm::vec3{x, y, z});
            w.getState().addObject(tmp);
        }
    }});
}

