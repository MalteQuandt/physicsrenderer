//
// Created by malte on 5/12/2022.
//

#include <window/WindowFactory.h>

using namespace std;
using namespace phyren;

// Generate a window context object that is wrapped in a shared pointer, as
// the destructor can only be called once!
std::shared_ptr<WindowContext>
WindowFactory::Create(WindowTypes type, unsigned int width, unsigned int height, const std::string &name) {
    switch (type) {
        case WindowTypes::BASE_WINDOW:
            return BaseWindow::create(width, height, name);
    }
    return nullptr;
}
