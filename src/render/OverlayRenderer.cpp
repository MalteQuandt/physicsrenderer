//
// Created by malte on 5/12/2022.
//

#include "render/OverlayRenderer.h"

#include "render/Cube.h"
#include "render/Sphere.h"
#include "render/Field.h"
#include "render/ModelLoader.h"
#include "render/GeneralModel.h"

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
    static float x{3}, y{0}, z{-5};
    static float scale{1};

    ImGui::SliderFloat("X-axis", &x, -10, 10);
    ImGui::SliderFloat("Y-axis", &y, -10, 10);
    ImGui::SliderFloat("Z-axis", &z, -10, 10);
    ImGui::SliderFloat("Scale", &scale, 0.01, 100);

    if(ImGui::Button("Create Cube")) {
        shared_ptr<object::Cube<3, float>> tmp{new object::Cube<3, float>{}};
        tmp->setScale(glm::vec<3, float>(scale, scale, scale));
        tmp->setPosition(glm::vec3{x, y, z});
        state.addObject(tmp);
    }
    if(ImGui::Button("Create Sphere")) {
        shared_ptr<object::Sphere<3, float>> tmp{new object::Sphere<3, float>{}};
        tmp->setScale(glm::vec<3, float>(scale, scale, scale));
        tmp->setPosition(glm::vec3{x, y, z});
        state.addObject(tmp);
    }
    if(ImGui::Button("Create Field")) {
        shared_ptr<object::Field<3, float>> tmp{new object::Field<3, float>{10}};
        tmp->setScale(glm::vec<3, float>(scale, scale, scale));
        tmp->setPosition(glm::vec3{x, y, z});
        state.addObject(tmp);
    }
    if(ImGui::Button("Create Model")) {
        shared_ptr<object::GeneralModel<3, float>> tmp{new object::GeneralModel<3, float>{R"(..\assets\models\backpack\backpack.obj)"}};
        tmp->setScale(glm::vec<3, float>(scale, scale, scale));
        tmp->setPosition(glm::vec3{x, y, z});
        state.addObject(tmp);
    }
}