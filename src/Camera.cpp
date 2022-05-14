//
// Created by malte on 5/12/2022.
//

#include "Camera.h"

#include <iostream>

using namespace std;
using namespace phyren;

phyren::Camera::Camera(glm::vec3 position, glm::vec3 worldUp, glm::vec3 front, float yaw, float pitch, float roll) : pos(
        position), worldUp(worldUp), front(front), yaw(yaw), pitch(pitch), roll(roll) {
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

    glm::vec3 worldFront{glm::normalize(glm::cross(worldUp, right))};
    // Calculate the front vector of the world
    switch (direction) {
        case Movement_Direction::FORWARD:
            pos += worldFront * velocity;
            break;
        case Movement_Direction::BACKWARD:
            pos -= worldFront* velocity;
            break;
        case Movement_Direction::LEFT:
            pos -= right * velocity;
            break;
        case Movement_Direction::RIGHT:
            pos += right * velocity;
            break;
        case Movement_Direction::DOWN:
            pos -= worldUp * velocity;
             break;
        case Movement_Direction::UP:
            pos += worldUp * velocity;
            break;
    }

}

void phyren::Camera::processMouseMovement(float xoff, float yoff) {
    xoff*=sensitivity;
    yoff*=sensitivity;
    yaw += xoff;
    pitch += yoff;
    // Make sure that the camera can not flip around
    if (pitch > 89.0f) {
        pitch = 89.0f;
    }
    if (pitch < -89.0f) {
        pitch = -89.0f;
    }
    update();
}

void phyren::Camera::processMouseScroll(float yoff) {
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

float phyren::Camera::getZoom() {
    return this->zoom;
}

void phyren::Camera::update() {
    /* Calculate the point on the sphere at center 0
     around the camera space with euler angles:
     x := cos(yaw)*cos(pitch)
     y := sin(pitch)
     z := sin(yaw)*cos(pitch)
     */
    glm::vec3 front{};
    front.x=glm::cos(glm::radians(yaw)) * cos(glm::radians(pitch));
    front.y=glm::sin(glm::radians(pitch));
    front.z=glm::sin(glm::radians(yaw)) * glm::cos(glm::radians(pitch));
    this->front=glm::normalize(front);
    // Calculate the rest of the camera/view-space coordinate system
    this->right = glm::normalize(glm::cross(this->front, worldUp));
    this->up = glm::normalize(glm::cross(right, this->front));
    /*we will ignore rotation for now, but it is just a matrix that will rotate about
    the front vector anyways, so fairly easy to implement*/
}
