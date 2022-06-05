//
// Created by malte on 5/12/2022.
//

#include "camera/Camera.h"


using namespace std;
using namespace phyren;

phyren::Camera::Camera(glm::vec3 position)
        : pos(
        position) {
}

glm::vec3 &phyren::Camera::getPosition() {
    return pos;
}

float phyren::Camera::getZoom() {
    return this->zoom;
}

void Camera::enable(Enabled_Operations_Camera operation) {
    this->enableFlags |= static_cast<unsigned int>(operation);
}

void Camera::disable(Enabled_Operations_Camera operation) {
    this->enableFlags &= ~static_cast<unsigned int>(operation);
}

bool Camera::isEnabled(Enabled_Operations_Camera operation) const {
    return this->enableFlags & static_cast<unsigned int>(operation);
}
void update() {}