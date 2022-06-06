//
// Created by malte on 5/12/2022.
//

#include "render/OverlayRenderer.h"

#include "render/Cube.h"

using namespace std;
using namespace phyren;

std::shared_ptr<OverlayRenderer> OverlayRenderer::instance(GLFWwindow* window, const string& glslVersion, const State<3, float>& state) {
    return make_shared<OverlayRenderer>(move(OverlayRenderer(window, glslVersion, state)));
}

OverlayRenderer::OverlayRenderer(GLFWwindow* window, const std::string& glslVersion, const State<3, float>& state) : state{
        const_cast<State<3, float> &>(state)}{
    // Setup Dear ImGui context
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO &io{ImGui::GetIO()};
    // Setup Platform/Renderer bindings, and install imgui's internal callbacks
    ImGui_ImplGlfw_InitForOpenGL(window, 1);
    ImGui_ImplOpenGL3_Init(("#version "+glslVersion).c_str());
    // Setup Dear ImGui style
    ImGui::StyleColorsDark();
}

void OverlayRenderer::setupCallbacks(GLFWwindow* window) {
    ImGui_ImplGlfw_InstallCallbacks(window);
}

void OverlayRenderer::render() {
    // feed inputs to dear imgui, start new frame
    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplGlfw_NewFrame();
    ImGui::NewFrame();

    // render your GUI
//    ImGui::ShowDemoWindow();

    // Render the window
    // -----------------
    generateWindow();

    // Render dear imgui into screen
    ImGui::Render();
    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
}

void OverlayRenderer::destroy(){
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();
}

void OverlayRenderer::generateWindow() {
    // TODO: Actually implement this in a child class
    static float x{0}, y{0}, z{0};
    ImGui::SliderFloat("X-axis", &x, -10, 10);
    ImGui::SliderFloat("Y-axis", &y, -10, 10);
    ImGui::SliderFloat("Z-axis", &z, -10, 10);

    if(ImGui::Button("Create")) {
        shared_ptr<object::Cube<3, float>> tmp{new object::Cube<3, float>{}};
        tmp->setPosition(glm::vec3{x, y, z});
        state.addObject(tmp);
    }
}