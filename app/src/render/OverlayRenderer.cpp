//
// Created by malte on 5/12/2022.
//

#include <render/OverlayRenderer.h>
#include <render/object/Field.tpp>

using namespace std;
using namespace phyren;
using namespace overlay;

std::shared_ptr<OverlayRenderer>
OverlayRenderer::instance(GLFWwindow *window, const string &glslVersion, State<3, float> &state) {
    return make_shared<OverlayRenderer>(move(OverlayRenderer(window, glslVersion, state)));
}

OverlayRenderer::OverlayRenderer(GLFWwindow *window, const std::string &glslVersion, State<3, float> &state)
        : state{make_unique<State<3, float>>(state)} {
    // Setup Dear ImGui context
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO &io{ImGui::GetIO()};
    // Setup Platform/Renderer bindings, and install ImGui's internal callbacks
    ImGui_ImplGlfw_InitForOpenGL(window, 1);
    ImGui_ImplOpenGL3_Init(("#version " + glslVersion).c_str());
    // Setup Dear ImGui style
    ImGui::StyleColorsDark();
}

void OverlayRenderer::setupCallbacks(GLFWwindow *window) {
    ImGui_ImplGlfw_InstallCallbacks(window);
}

void OverlayRenderer::render() {
    // feed inputs to dear imgui, start new frame
    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplGlfw_NewFrame();
    ImGui::NewFrame();
    // render the overlay window(s)
    for (auto &window: windows) {
        window.render();
    }
    // Render dear imgui into screen
    ImGui::Render();
    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
}

void OverlayRenderer::destroy() {
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();
}

void OverlayRenderer::registerWindow(const OverlayWindow &window) {
    windows.push_back(window);
}

void OverlayRenderer::registerWindow(std::shared_ptr<OverlayWindow> window) {
    windows.push_back(*window);
}

void OverlayRenderer::removeWindow(const OverlayWindow &window) {
    remove_if(windows.begin(), windows.end(), [&window](OverlayWindow &ow) -> bool { return &window == &ow; });
}