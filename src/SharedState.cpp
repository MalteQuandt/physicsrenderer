//
// Created by malte on 5/13/2022.
//

#include "SharedState.h"

using namespace phyren;

std::shared_ptr<InputController> SharedState::controller{nullptr};

std::shared_ptr<Camera> SharedState::camera{nullptr};