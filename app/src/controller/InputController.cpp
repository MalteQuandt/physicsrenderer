//
// Created by malte on 5/7/2022.
//

#include "controller/InputController.h"

using namespace phyren;
using namespace std;

std::shared_ptr<InputController> InputController::instance() {
    return make_shared<InputController>(move(InputController()));
}

bool InputController::isPressed(unsigned int key) {
    if (this->keymapping.contains(static_cast<int>(key))) {
        return this->keymapping.at(static_cast<int>(key));
    }
    this->keymapping.emplace(key, false);
    return false;
}

void InputController::press(unsigned int key) {
    if (!isPressed(static_cast<int>(key))) {
        this->keymapping.at(static_cast<int>(key)) = true;
    }
}

void InputController::released(unsigned int key) {
    if (isPressed(static_cast<int>(key))) {
        this->keymapping.at(static_cast<int>(key)) = false;
    }
}

void InputController::toggle(unsigned int key) {
    if (this->keymapping.contains(static_cast<int>(key))) {
        this->keymapping.at(static_cast<int>(key)) = !this->keymapping.at(static_cast<int>(key));
    }
        // Consider the key as not pressed, if it is not yet in the list, therefore place it to true
    else { this->keymapping.emplace(key, true); }
}