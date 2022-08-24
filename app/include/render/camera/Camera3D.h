//
// Created by malte on 5/16/2022.
//

#ifndef PHYSICS_RENDERER_CAMERA3D_H
#define PHYSICS_RENDERER_CAMERA3D_H

#include "Camera.h"

#define STARTING_YAW -90.0f
#define STARTING_PITCH 0.0f
#define STARTING_ROLL 0.0f

namespace phyren {
    /**
     * Camera created for a 3-dimensional world
     */
    class Camera3D : public Camera {
    public:
        explicit Camera3D(glm::vec3 position = glm::vec3{0.0f, 0.0f, 0.0f},
                glm::vec3 worldUp = glm::vec3{0.0f, 1.0f, 0.0f},
                glm::vec3 front = glm::vec3{0.0f, 0.0f, -1.0f}, float yaw = STARTING_YAW,
        float pitch = STARTING_PITCH, float roll = STARTING_ROLL);
        /**
         * Calculate the look-at matrix from the camera data
         *
         * @return the look-at matrix (matrix that transforms world space vertices into view space)
         */
        glm::mat4 getViewMatrix() override;
        /**
         * Calculate the new position vector from user input
         *
         * @param direction The direction in which the camera will move
         * @param delta the time the last frame took
         */
        void processMovement(Movement_Direction direction, float delta) override;
        /**
         * Process the mouse movement.
         * Expects the offset in x and y direction
         *
         * @param xoff offset in x direction on screen
         * @param yoff offset in y direciton on screen
         */
        void processMouseMovement(float xoff, float yoff) override;

        /**
         * Calculate the scroll value of the user input
         *
         * @param yoff the offset on the scrollwheels axis
         */
        void processMouseScroll(double yoff) override;

    private:
        /** The up vector of world space*/
        glm::vec3 worldUp{};
        // Euler angles
        float yaw{STARTING_YAW};
        float pitch{STARTING_PITCH};
        float roll{STARTING_ROLL};
        // Secondary Values
        // ----------------
        // The axes of the camera space coordinate system
        /** camera space x-axis */
        glm::vec3 right{};
        /** camera space y-axis */
        glm::vec3 up{};
        /** camera space z-axis */
        glm::vec3 front;

        /**
        * Update camera coordinate system from updated euler angles
        * and position vector.
        * Updates the *secondary values*
        */
        void update();
    };
}
// Remove defines
#undef YAW
#undef PITCH
#undef ROLL

#endif //PHYSICS_RENDERER_CAMERA3D_H
