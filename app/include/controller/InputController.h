//
// Created by malte on 5/7/2022.
//

#ifndef PHYSICS_RENDERER_INPUTCONTROLLER_H
#define PHYSICS_RENDERER_INPUTCONTROLLER_H

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <map>
#include <memory>

namespace phyren {
    /**
    * Abstract class that handles the input
    */
    class InputController {
    public:
        /**
         * Create an input controller instance with the data it needs to manipulate
         *
         * @return an instance of this class
         */
        static std::shared_ptr<InputController> instance();
         /**
          * Check, if the key is currently pressed
          *
          * @param key the glfw value of the key checked
          *
          * @return if the key is pressed
          */
         virtual bool isPressed(unsigned int key);
         /**
          * Set the specific key as being pressed
          *
          * @param key the key that was pressed
          */
         virtual void press(unsigned int key);

         /**
          * Set the specific key as being released
          *
          * @param key the key that was released
          */
         virtual void released(unsigned int key);
         /**
          * Toggle the specified key
          *
          * @param key the key to be toggled
          */
          virtual void toggle(unsigned int key);

    private:
         // Map to see which key is currently active
         std::map<int, bool> keymapping{};
         // Create input controller, is not accessible and should be created from the instance() method
         explicit InputController() = default;
    };
}


#endif //PHYSICS_RENDERER_INPUTCONTROLLER_H
