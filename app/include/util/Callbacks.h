#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <iostream>

#include <SharedState.h>

// Collection of callback methods for the main application
namespace phyren {
    class Callbacks {
    public:
        /**
         * Callback method for glfw that is invoked when glfw encounters an error
         */
        static void error_callback(int, const char *);

        /**
         * Callback for actions that regard keys in glfw
         */
        static void key_callback(GLFWwindow *, int, int, int, int);

        /**
         * Handle the scroll callback for glfw
         */
        static void scroll_callback(GLFWwindow *, double, double);

        /**
         * Handle mouse movement callback for glfw
         */
        static void mouse_movement_callback(GLFWwindow *, double, double);

    private:
        /*
          * Constants used for the mouse movement callback.
          * Not exposed to the rest of the application
          */
        static bool firstMouse;
        static float X;
        static float Y;
    };
}