//
// Created by malte on 5/12/2022.
//

#ifndef PHYSICS_RENDERER_WINDOWCONTEXT_H
#define PHYSICS_RENDERER_WINDOWCONTEXT_H

#include "glad/glad.h"
#include "GLFW/glfw3.h"

#include "controller/InputController.h"

#include <memory>

namespace phyren {
    /**
     * Abstract base class that encapsulates an glfw window. Can be inherited from to create more specific behavior
     */
    class WindowContext {
    public:
        /**
         * Destroy this window and call it's terminate method
         */
        virtual ~WindowContext();
        /**
         * Make this window context the current context
         */
        virtual void makeCurrent();

        /**
         * Get the raw GLFWwindow pointer wrapped by this object
         */
        virtual GLFWwindow* getRaw();
    protected:
        // Opaque window object
        GLFWwindow* window{nullptr};

        /**
         * Create an object of this type.
         * The creation of this object may fail,
         * thus we create a setup method.
         *
         * @return shared pointer to actual object, OR nullptr if failed
         */
        static std::shared_ptr<WindowContext> create();
        /**
         * Create simple wrapper around window object.
         *
         * @attention Should only be created from the WindowFactory class (through the create(controller) method)!
         *
         * @param window
         */
        explicit WindowContext(GLFWwindow* window);
        // Disable creation of this object, except from the factory
        explicit WindowContext() = delete;

        // Make the window factory able to create the window object
        friend class WindowFactory;
    };

}


#endif //PHYSICS_RENDERER_WINDOWCONTEXT_H
