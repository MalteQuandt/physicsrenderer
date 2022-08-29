#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <controller/InputController.h>
#include <Constants.h>

#include <memory>

namespace phyren {
    /**
     * Abstract base class that encapsulates an glfw window. Can be inherited from to create more specific behavior
     */
    class WindowContext {
    public:

        /**
         * Make this window context the current context
         */
        virtual void makeCurrent();

        /**
         * Get the raw GLFWwindow pointer wrapped by this object
         */
        virtual GLFWwindow *get();

        /**
         * Get the width of the window
         */
        virtual unsigned int getWidth();

        /**
         * Get the height of the window
         */
        virtual unsigned int getHeight();

        /**
         * Check, if the window is maximized or not
         */
        virtual bool isMaximized();

        // Disable creation of this object, except from the factory
        explicit WindowContext() = delete;

        // Rule of 5
        // ---------
        /* Remove the ability to create a copy of this object, as copying leaves the possibility
         * open to delete the referenced window*/
        WindowContext(const WindowContext &) = delete;
        WindowContext(WindowContext &&) noexcept;

        WindowContext &operator=(WindowContext &&) noexcept;
        WindowContext &operator=(const WindowContext &) = delete;

        /**
        * Destroy this window and call it's terminate method
        */
        virtual ~WindowContext();

        // Window-Specific Callbacks:
        // --------------------------
        /**
        * Callback for the change in window size so that the viewport size can be
        * adapted
        *
        * @param window the glfw window
        */
        static void framebuffer_size_callback(GLFWwindow *, int, int);

        /**
         * @brief The actual implementation of the callback.
         */
        virtual void framebuffer_size_callback_internal(GLFWwindow *, int, int);

        /**
         * @brief Setup the resize callback.
         */
        virtual void setupResizeCallback();

    protected:
        // Opaque window object
        GLFWwindow *window{nullptr};
        // The window pointer of the currently bound window pointer
        void * windowPointer{nullptr};
        // The size of the window
        unsigned int width{0};
        unsigned int height{0};
        // If the window is maximized or not
        bool maximized{false};

        /**
         * Create an object of this type.
         * The creation of this object may fail,
         * thus we create a setup method.
         *
         * @return shared pointer to actual object, OR nullptr if failed
         */
        static std::shared_ptr<WindowContext> create();

        /**
         * @brief Create simple wrapper around window object.
         *
         * @attention Should only be created from the WindowFactory class (through the create() method)!
         *
         * @param window the glfw window this class wraps around
         * @param width the initial width of the window
         * @param height the initial height of the window
         */
        explicit WindowContext(GLFWwindow *window, unsigned int width, unsigned int height);

        /**
         * @brief Set the width of the window.
         *
         * @param width the width of the window.
         */
        void setWidth(unsigned int width);

        /**
         * @brief Set the height of the window.
         *
         * @param height the height of the window.
         */
        void setHeight(unsigned int height);

        // Make the window factory able to create the window object
        friend class WindowFactory;

        /**
         * @brief Set the dimensions of this window context.
         *
         * @param width the new width of this window.
         * @param height the new height of this window.
         */
        void setDimensions(unsigned int width, unsigned int height);
    };
}