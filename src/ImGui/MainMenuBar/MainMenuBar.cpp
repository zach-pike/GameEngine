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

        if (ImGui::BeginMenu("View")) {
            ImGui::MenuItem("Scene explorer", nullptr, controls.sceneExplorerOpen);
            ImGui::MenuItem("Asset explorer", nullptr, controls.assetExplorerOpen);
            ImGui::MenuItem("Logger", nullptr, controls.loggerOpen);
            ImGui::MenuItem("Scene Editor", nullptr, controls.sceneEditorOpen);
            
            ImGui::EndMenu();
        }

        ImGui::EndMainMenuBar();
    }
}