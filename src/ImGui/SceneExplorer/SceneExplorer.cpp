#include "SceneExplorer.hpp"

SceneExplorer::SceneExplorer() {

}

SceneExplorer::~SceneExplorer() {

}

void SceneExplorer::setScene(std::shared_ptr<Scene> scene) {
    currentScene = scene;
}

void SceneExplorer::render(ImGuiWindowFlags extraFlags, std::shared_ptr<Shape>& selectedObject) {
    if (!open) return;
    ImGui::Begin("Scene Explorer", &open, extraFlags);

        if (currentScene == nullptr) {
            ImGui::Text("No Scene selected");

            ImGui::End();
            return;
        }

        ImGui::SetNextItemOpen(true);
        if (ImGui::TreeNode(currentScene->getSceneName().c_str())) {
            ImGui::SetNextItemOpen(true);
            if (ImGui::TreeNode("Objects")) {
                if (ImGui::BeginTable("objectList", 2, ImGuiTableFlags_Borders | ImGuiTableFlags_Resizable)) {
                    ImGui::TableSetupColumn("#");
                    ImGui::TableSetupColumn("Type");

                    ImGui::TableHeadersRow();

                    char indexStr[20];

                    auto& objs = currentScene->getObjects();
                    for (int i=0; i<objs.size(); i++) {
                        auto& obj = objs.at(i);

                        bool isSelectedItem = obj == selectedObject;

                        ImGui::TableNextColumn();
                        int indexStrSize = sprintf(indexStr, "%d", i);
                        indexStr[indexStrSize] = '\0';

                        if (ImGui::Selectable(indexStr, isSelectedItem, ImGuiSelectableFlags_SpanAllColumns | ImGuiSelectableFlags_AllowOverlap)) {
                            selectedObject = obj;
                        }

                        ImGui::TableNextColumn();
                        ImGui::Text("%s", Shape::getModelTypeString(obj->getObjectType()));
                    }
                }
                
                ImGui::EndTable();
                ImGui::TreePop();
            }


            ImGui::TreePop();
        }

    ImGui::End();
}