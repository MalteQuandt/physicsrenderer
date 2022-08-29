//
// Created by malte on 8/26/2022.
//

#pragma once

#include <engine/Entity3.h>
#include <render/overlay/OverlayRenderer.h>
#include <render/camera/Camera.h>
#include <engine/State.h>
#include <window/WindowContext.h>
#include <Logger.h>

namespace phyren::engine{
    /**
     * The main engine of the application. Provide access points to the most common functions and is a state machine
     */
    class Engine final {
    public:
        /**
         * @brief   Initialize the engine.
         *
         * @param   argc the amount of console arguments to process.
         * @param   argv the console arguments to process.
         *
         * @return  the error code, or 0 if there was no error.
         */
        explicit Engine(int argc, char ** argv);

        /**
         * @brief   Start the engine's execution, and the applications main loop.
         *
         * @return  the error code from the main loop of the engine,
         *          or 0 if there was no error.
         */
        int run();

        /**
         * De-initialize the engine.
         */
        ~Engine();

        // Getter & Setter
        // ---------------

        logging::Logger& getLogger();
        WindowContext& getWindow();
        overlay::OverlayRenderer& getOverlayRenderer();
        Camera& getCamera();
        InputController& getController();
        ShaderProgram& getShader();

        // Rule of 5
        // ---------
        Engine(const Engine&) = delete;
        Engine(Engine&&) = delete;

        Engine& operator=(const Engine&) = delete;
        Engine& operator=(Engine&&) = delete;

    private:
        // Engine State
        // ------------
        // The window that is the viewpoint into the application
        std::unique_ptr<WindowContext> window{nullptr};
        // The overlay handler
        std::unique_ptr<overlay::OverlayRenderer> overlay{nullptr};
        // Current State of the physics system
        std::unique_ptr<engine::State> currentState{nullptr};
        // The camera into the world space
        std::unique_ptr<Camera> camera{nullptr};
        // The input controller instance for this engine
        std::unique_ptr<InputController> controller{nullptr};
        // The currently bound shader for the engine
        std::unique_ptr<ShaderProgram> shader{nullptr};
        // The logger for the engine
        std::unique_ptr<logging::Logger> logger;
        // Configuration of the engine, usually set from the start
        struct {
            // If the logger should be enabled
            bool useLogger{true};
            // Render the polygons as the lines they represent and do not fill them
            bool renderAsLines{false};
            // What integration method should be used
            enum class integration_methods : uint8_t {
                explicitEuler=0,
                semiImplicitEuler=1,
                verlet=2,
                rk4=3
            } integrationMethod{integration_methods::explicitEuler};
        } configuration;

        // Privates
        // --------
        //
        /**
         * @brief   Parse the console argument and set up the initial engine state.
         *
         * @param   argc the amount of console arguments to process.
         * @param   argv the console arguments to process.
         */
        void _parseConsoleArguments(int argc, char ** argv);
        /**
         * @brief
         */
        void _setupOpenGL();
    };
}