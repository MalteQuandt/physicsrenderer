//
// Created by malte on 6/9/2022.
//

#ifndef PHYSICS_RENDERER_OVERLAYWINDOW_H
#define PHYSICS_RENDERER_OVERLAYWINDOW_H

#include <memory>
#include <render/State.h>
#include <functional>

namespace phyren {
    namespace overlay {
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
            static std::shared_ptr<OverlayWindow> instance(std::shared_ptr<State<3, float>> state, const auto &lambda);

            /**
             * Generate a new window and provide it the current state of the application
             * where the lambda provides the window creation code
             *
             * @param state the state of the renderer
             * @param lambda creation of the window lambda
             */
            explicit OverlayWindow(std::shared_ptr<State<3, float>> state, const std::function<void(OverlayWindow&)> &lambda);

            /**
             * render the window in the current frame
             */
            virtual void render();

            /**
             * Get the state that this window is connected to
             *
             * @return the state of this window
             */
            virtual std::shared_ptr<State<3, float>> &getState() {
                return this->state;
            }

            // Rule of 5
            OverlayWindow(const OverlayWindow &);

            OverlayWindow(OverlayWindow &&);

            OverlayWindow &operator=(OverlayWindow &&);

            OverlayWindow &operator=(const OverlayWindow &);

        private:
            // State of the render engine
            std::shared_ptr<State<3, float>> state;
            // The code to generate this window
            std::function<void(OverlayWindow &)> code;

            // The code used to create this window
        };
    }
}


#endif //PHYSICS_RENDERER_OVERLAYWINDOW_H
