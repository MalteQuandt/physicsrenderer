//
// Created by malte on 5/12/2022.
//

#ifndef PHYSICS_RENDERER_CAMERA_H
#define PHYSICS_RENDERER_CAMERA_H

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/gtc/matrix_transform.hpp>

#define STARTING_YAW -90.0f
#define STARTING_PITCH 0.0f
#define STARTING_ROLL 0.0f
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
     * Camera base class
     */
    class Camera {
    public:
        explicit Camera(glm::vec3 position = glm::vec3{0.0f, 0.0f, 0.0f}, glm::vec3 worldUp = glm::vec3{0.0f, 1.0f, 0.0f},
                        glm::vec3 front = glm::vec3{0.0f, 0.0f, -1.0f}, float yaw = STARTING_YAW,
                        float pitch = STARTING_PITCH, float roll = STARTING_ROLL);

        /**
         * Calculate the look-at matrix from the camera data
         *
         * @return the look-at matrix (matrix that transforms world space vertices into view space)
         */
        virtual glm::mat4 getViewMatrix();

        /**
         * Calculate the new position vector from user input
         *
         * @param direction The direction in which the camera will move
         * @param delta the time the last frame took
         */
        virtual void processMovement(Movement_Direction direction, float delta);

        /**
         * Process the mouse movement.
         * Expects the offset in x and y direction
         *
         * @param xoff offset in x direction on screen
         * @param yoff offset in y direciton on screen
         */
        virtual void processMouseMovement(float xoff, float yoff);

        /**
         * Calculate the scroll value of the user input
         *
         * @param yoff the offset on the scrollwheels axis
         */
        virtual void processMouseScroll(float yoff);

        /**
         * Get the current position of the camera in world space
         *
         * @return camera position in world space
         */
         virtual glm::vec3& getPosition();
         /**
          * Get the current zoom value
          *
          * @return the current zoom value of this camera object
          */
         virtual float getZoom();
    private:
        // Primary Values
        // --------------
        /** Position of the camera in world space*/
        glm::vec3 pos{};
        /** The up vector of world space*/
        glm::vec3 worldUp{};
        float speed{SPEED};
        float sensitivity{SENSITIVITY};
        float zoom{STARTING_ZOOM};
        // Euler angles
        float yaw{STARTING_YAW};
        float pitch{STARTING_PITCH};
        float roll{STARTING_ROLL};
        // Secondary Values
        // ----------------
        // The axes of the camera space coordinate system
        /** camera space x-axis */
        glm::vec3 right;
        /** camera space y-axis */
        glm::vec3 up;
        /** camera space z-axis */
        glm::vec3 front;

        /**
         * Update camera coordinate system from updated euler angles
         * and position vector.
         * Updates the *secondary values*
         */
        virtual void update();
    };
}

// Remove defines
#undef YAW
#undef PITCH
#undef SENSITIVITY
#undef ZOOM
#undef ROLL

#endif //PHYSICS_RENDERER_CAMERA_H
