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
    if(this->keymapping.contains(key)) {
        return this->keymapping.at(key);
    }
    this->keymapping.emplace(key, false);
    return false;
}

void InputController::press(unsigned int key) {
    this->keymapping.emplace(key, true);
}

void InputController::released(unsigned int key) {
    this->keymapping.emplace(key, false);
}

void InputController::toggle(unsigned int key) {
    this->keymapping.emplace(key, !isPressed(key));
}

void InputController::process(float delta) {
    // TODO: Process the input data from the user
}