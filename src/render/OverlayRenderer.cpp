//
// Created by malte on 5/12/2022.
//

#include "render/OverlayRenderer.h"

using namespace std;
using namespace phyren;

std::shared_ptr<OverlayRenderer> OverlayRenderer::instance(GLFWwindow* window, const string& glslVersion) {
    return make_shared<OverlayRenderer>(move(OverlayRenderer(window, glslVersion)));
}

OverlayRenderer::OverlayRenderer(GLFWwindow* window, const std::string& glslVersion) {
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

void OverlayRenderer::render() {
    // feed inputs to dear imgui, start new frame
    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplGlfw_NewFrame();
    ImGui::NewFrame();

    // render your GUI
    ImGui::ShowDemoWindow();

    // Render dear imgui into screen
    ImGui::Render();
    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
}

void OverlayRenderer::destroy(){
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();
}