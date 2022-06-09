//
// Created by malte on 6/9/2022.
//

#include "render/OverlayWindow.h"

using namespace phyren;
using namespace std;
using namespace overlay;

std::shared_ptr<OverlayWindow> OverlayWindow::instance(std::shared_ptr<State<3, float>> state, const auto &lambda) {
    return make_shared<OverlayWindow>(move(OverlayWindow{state, lambda}));
}

OverlayWindow::OverlayWindow(std::shared_ptr<State<3, float>> state, const std::function<void(OverlayWindow&)> &lambda) : state{state}, code{lambda} {}

void OverlayWindow::render() {
    this->code(*this);
}

OverlayWindow::OverlayWindow(OverlayWindow &&ow) : code{ow.code}, state(state) {}

OverlayWindow::OverlayWindow(const OverlayWindow &ow) : code(ow.code), state(ow.state) {}

OverlayWindow &OverlayWindow::operator=(const OverlayWindow &ow) {
    if (this != &ow) {
        this->code = ow.code;
        this->state = ow.state;
    }
    return *this;
}

OverlayWindow &OverlayWindow::operator=(OverlayWindow &&ow) {
    if (this != &ow) {
        swap(this->code, ow.code);
        swap(this->state, ow.state);
    }
    return *this;
}
