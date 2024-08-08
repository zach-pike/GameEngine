#include "MainMenuBar.hpp"

#include "imgui/imgui.h"

MainMenuBar::MainMenuBar() {}
MainMenuBar::~MainMenuBar() {}

void MainMenuBar::render() {
    if (ImGui::BeginMainMenuBar()) {
        if (ImGui::BeginMenu("File")) {
            ImGui::MenuItem("Save");
            ImGui::MenuItem("Save As", nullptr);
            ImGui::EndMenu();
        }

        ImGui::EndMainMenuBar();
    }
}