#include "SceneExplorer.hpp"

SceneExplorer::SceneExplorer() {

}

SceneExplorer::~SceneExplorer() {

}

void SceneExplorer::setScene(std::shared_ptr<GameScene> scene) {
    currentScene = scene;
}

void SceneExplorer::render(ImGuiWindowFlags extraFlags) {
    if (!open) return;
    ImGui::Begin("Scene Explorer", &open, extraFlags);

        if (currentScene == nullptr) {
            ImGui::Text("No Scene selected");

            ImGui::End();
            return;
        }
    
        if (ImGui::TreeNode(currentScene->getSceneName().c_str())) {
            if (ImGui::TreeNode("Objects")) {
                if (ImGui::BeginTable("objectList", 2, ImGuiTableFlags_Borders | ImGuiTableFlags_Resizable)) {
                    ImGui::TableSetupColumn("#");
                    ImGui::TableSetupColumn("Type");

                    ImGui::TableHeadersRow();

                    auto& objs = currentScene->getObjects();
                    for (int i=0; i<objs.size(); i++) {
                        auto& obj = objs.at(i);

                        ImGui::TableNextColumn();
                        ImGui::Text("%d", i);

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