//
// Created by malte on 5/12/2022.
//

#include "Camera.h"

phyren::Camera::Camera(glm::vec3 position, glm::vec3 up, glm::vec3 front, float yaw, float pitch, float roll) : pos(
        position), up(up), front(front), yaw(yaw), pitch(pitch), roll(roll) {
    // Generate the secondary values and the camera space coordinate system
    update();
}

glm::mat4 phyren::Camera::getViewMatrix() {
    // Generate the look-at matrix, which is nothing more than
    // the inverse matrix of the model matrix of the camera
    return glm::lookAt(pos, pos + front, up);
}

void phyren::Camera::processMovement(phyren::Movement_Direction direction, float delta) {
    // Calculate the current velocity in this (technically last) frame
    float velocity{speed * delta};
    // Calculate the front vector of the world
    switch (direction) {
        case Movement_Direction::FORWARD:
            pos += front * velocity;
            return;
        case Movement_Direction::BACKWARD:
            pos -= front * velocity;
            return;
        case Movement_Direction::LEFT:
            pos += right * velocity;
            return;
        case Movement_Direction::RIGHT:
            pos -= right * velocity;
            return;
        case Movement_Direction::DOWN:
            pos += worldup * velocity;
            return;
        case Movement_Direction::UP:
            pos -= worldup * velocity;
            return;
    }
}

void phyren::Camera::processMouseMovement(float xoff, float yoff) {
    yaw += xoff * sensitivity;
    pitch += yoff * sensitivity;
    // Make sure that the camera can not flip around
    if (pitch > 89.0f) {
        pitch = 89.0f;
    }
    if (pitch < -89.0f) {
        pitch = -89.0f;
    }
}

void phyren::Camera::processMouseScroll(float yoff, float delta) {
    this->zoom -= static_cast<float>(yoff);
    // Let the value be between a given range
#define MIN_ZOOM 1.0f
#define MAX_ZOOM 90.0f
    if (this->zoom < MIN_ZOOM) {
        this->zoom = MIN_ZOOM;
    }
    if (this->zoom > MAX_ZOOM) {
        this->zoom = MAX_ZOOM;
    }
#undef MIN_ZOOM
#undef MAX_ZOOM
}

glm::vec3 &phyren::Camera::getPosition() {
    return pos;
}

void phyren::Camera::update() {
    /* Calculate the point on the sphere at center 0
     around the camera space with euler angles:
     x := cos(yaw)*cos(pitch)
     y := sin(pitch)
     z := sin(yaw)*cos(pitch)
     */
    front=glm::normalize(glm::vec3{
            glm::cos(glm::radians(yaw)) * cos(glm::radians(pitch)),
            glm::sin(glm::radians(pitch)),
            glm::sin(glm::radians(yaw)) * glm::cos(glm::radians(pitch))
    });
    // Calculate the rest of the camera/view-space coordinate system
    this->right=glm::normalize(glm::cross(front, worldup));
    this->up=glm::normalize(glm::cross(right, front));
    /*we will ignore rotation for now, but it is just a matrix that will rotate about
    the front vector anyways, so fairly easy to implement*/
}
