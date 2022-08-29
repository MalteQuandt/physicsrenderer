#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/gtc/matrix_transform.hpp>

#define SPEED 2.5f
#define SENSITIVITY 0.1f
#define STARTING_ZOOM 45.0f

namespace phyren {
    /**
     * Enum for directions this camera can take
     */
    enum class Movement_Direction : unsigned int {
        FORWARD,
        BACKWARD,
        LEFT,
        RIGHT,
        DOWN,
        UP
    };
    /**
     * What parts of this camera are enabled
     */
    enum class Enabled_Operations_Camera {
        SCROLL = 1,
        MOUSE_MOVEMENT = 2,
        KEY_PRESS = 4
    };

    /**
     * Camera base class
     */
    class Camera {
    public:
        explicit Camera(glm::vec3 position = glm::vec3{0.0f, 0.0f, 0.0f});

        /**
         * Calculate the look-at matrix from the camera data
         *
         * @return the look-at matrix (matrix that transforms world space vertices into view space)
         */
        virtual glm::mat4 getViewMatrix() = 0;

        /**
         * Calculate the new position vector from user input
         *
         * @param direction The direction in which the camera will move
         * @param delta the time the last frame took
         */
        virtual void processMovement(Movement_Direction direction, float delta) = 0;

        /**
         * Process the mouse movement.
         * Expects the offset in x and y direction
         *
         * @param xoff offset in x direction on screen
         * @param yoff offset in y direciton on screen
         */
        virtual void processMouseMovement(float xoff, float yoff) = 0;

        /**
         * Calculate the scroll value of the user input
         *
         * @param yoff the offset on the scrollwheels axis
         */
        virtual void processMouseScroll(double yoff) = 0;

        /**
         * Get the current position of the camera in world space
         *
         * @return camera position in world space
         */
        virtual glm::vec3 &getPosition();

        /**
         * Get the current zoom value
         *
         * @return the current zoom value of this camera object
         */
        virtual float getZoom();

        /**
         * Enable the camera attribute
         */
        void enable(Enabled_Operations_Camera operation);

        /**
         * Disable the camera attribute
         */
        void disable(Enabled_Operations_Camera operation);

        /**
        * Check if the camera attribute is enabled
        */
        [[nodiscard]]
        bool isEnabled (Enabled_Operations_Camera operation) const;

    protected:
        // Primary Values
        // --------------
        /** Position of the camera in world space*/
        glm::vec3 pos{};
        float speed{SPEED};
        float sensitivity{SENSITIVITY};
        float zoom{STARTING_ZOOM};
        unsigned int enableFlags{0};

         /**
         * Update camera coordinate system from updated euler angles
         * and position vector.
         * Updates the *secondary values*
         */
        virtual void update() = 0;
    };
}

// Remove defines
#undef SENSITIVITY
#undef ZOOM
#undef SPEED