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
    if (this->keymapping.contains(key)) {
        return this->keymapping.at(key);
    }
    this->keymapping.emplace(key, false);
    return false;
}

void InputController::press(unsigned int key) {
    if (!isPressed(key)) {
        this->keymapping.at(key) = true;
    }
}

void InputController::released(unsigned int key) {
    if (isPressed(key)) {
        this->keymapping.at(key) = false;
    }
}

void InputController::toggle(unsigned int key) {
    if (this->keymapping.contains(key)) { this->keymapping.at(key) = !this->keymapping.at(key); }
        // Consider the key as not pressed, if it is not yet in the list, therefore place it to true
    else { this->keymapping.emplace(key, true); }
}