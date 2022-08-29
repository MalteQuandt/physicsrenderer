//
// Created by malte on 6/9/2022.
//

#include "render/overlay/OverlayWindow.h"

using namespace phyren;
using namespace std;
using namespace overlay;

std::shared_ptr<OverlayWindow> OverlayWindow::instance(std::shared_ptr<State<3, float>> state, const auto &lambda, std::string name) {
    return make_shared<OverlayWindow>(move(OverlayWindow{state, lambda, name}));
}

void OverlayWindow::render() {
    this->code(*this);
}

State<3, float> &OverlayWindow::getState() {
    return this->state;
}

std::string &OverlayWindow::getName() {
    return this->name;
}

OverlayWindow::OverlayWindow(OverlayWindow &&ow) noexcept : code{ow.code}, state(ow.state), name{ow.name} {}
OverlayWindow::OverlayWindow(const OverlayWindow &ow) : code(ow.code), state(ow.state), name{ow.name} {}

OverlayWindow::OverlayWindow(std::shared_ptr<State<3, float>> state, const std::function<void(OverlayWindow&)> &lambda, std::string name) : state{*state.get()}, code{lambda}, name{name} {}
OverlayWindow::OverlayWindow(State<3, float>& state, const std::function<void(OverlayWindow&)> &lambda, std::string name) : state{state}, code{lambda}, name{name} {}

OverlayWindow &OverlayWindow::operator=(const OverlayWindow &ow) {
    if (this != &ow) {
        this->code = ow.code;
        this->state = ow.state;
        this->name = ow.name;
    }
    return *this;
}

OverlayWindow &OverlayWindow::operator=(OverlayWindow &&ow) noexcept {
    if (this != &ow) {
        swap(this->code, ow.code);
        swap(this->state, ow.state);
        swap(this->name, ow.name);
    }
    return *this;
}
