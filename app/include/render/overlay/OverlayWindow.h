// Created by malte on 6/9/2022.

#pragma once

#include <memory>
#include <render/object/State.h>
#include <functional>

namespace phyren::overlay {
    /**
     * Representation of a simple window for the overlay renderer
     */
    class OverlayWindow {
    public:
        /**
         * Generate a new window instance
         *
         * @param lambda the code to use for the window
         * @param state the state of the renderer
         *
         * @return the window instance
         */
        static std::shared_ptr<OverlayWindow> instance(std::shared_ptr<State<3, float>> state, const auto &lambda, std::string name="Debug");

        /**
         * Generate a new window and provide it the current state of the application
         * where the lambda provides the window creation code
         *
         * @param state the state of the renderer
         * @param lambda creation of the window lambda
         */
        explicit OverlayWindow(std::shared_ptr<State<3, float>> state, const std::function<void(OverlayWindow&)> &lambda, std::string name="Debug");
        explicit OverlayWindow(State<3, float>& state, const std::function<void(OverlayWindow&)> &lambda, std::string name="Debug");

        /**
         * Render the window in the current frame
         */
        virtual void render();

        /**
         * Get the state that this window is connected to
         *
         * @return the state of this window
         */
        virtual State<3, float> &getState();

        /**
         * Get the name of the window.
         *
         * @return the name of the current window.
         */
        virtual std::string& getName();

        // Rule of 5
        // ---------
        OverlayWindow(const OverlayWindow &);
        OverlayWindow(OverlayWindow &&) noexcept;

        OverlayWindow &operator=(OverlayWindow &&) noexcept;
        OverlayWindow &operator=(const OverlayWindow &);

    private:
        // State of the render engine
        State<3, float>& state;
        // The code to generate this window
        std::function<void(OverlayWindow &)> code;
        // The name of this window
        std::string name;

        // The code used to create this window
    };
}