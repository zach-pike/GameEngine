#include "AssetExplorer.hpp"

#include "imgui/imgui.h"

#include <iostream>

AssetExplorer::AssetExplorer() {
    folderTexture.loadFromFilePath("resources/folder.png");
    fileTexture.loadFromFilePath("resources/file.png");

    currentPath = fs::absolute(".\\gameData");
}

AssetExplorer::~AssetExplorer() {

}

void AssetExplorer::render() {
    ImGui::Begin("Asset Explorer");
        std::string path = currentPath.string();

        ImGui::Text(path.c_str());

        int key = 0;

        if (ImGui::BeginTable("Files", 5, ImGuiTableFlags_Borders | ImGuiTableFlags_Resizable)) {
            ImGui::TableSetupColumn("Type");
            ImGui::TableSetupColumn("Filename");
            ImGui::TableSetupColumn("File extension");
            ImGui::TableSetupColumn("Size");

            ImGui::TableHeadersRow();

            // Display option to go up a directory
            ImGui::TableNextColumn();
            ImGui::Text("Directory");

            ImGui::TableNextColumn();
            ImGui::Text("..");

            ImGui::TableNextColumn();
            ImGui::TableNextColumn();
            ImGui::TableNextColumn();
            if (ImGui::Button("Navigate")) {
                currentPath = currentPath.parent_path();
                
                ImGui::EndTable();
                ImGui::End();
                return;
            }


            for (auto& item : fs::directory_iterator(currentPath)) {
                if (item.is_directory()) {
                    ImGui::TableNextColumn();
                    ImGui::Text("Directory");

                    std::string name = item.path().stem().string();
                    ImGui::TableNextColumn();
                    ImGui::Text(name.c_str());

                    ImGui::TableNextColumn();
                    ImGui::TableNextColumn();

                    ImGui::Text("N/a");

                    ImGui::TableNextColumn();
                    ImGui::PushID(key);
                    if (ImGui::Button("Navigate")) {
                        currentPath = item.path();
                        

                        ImGui::PopID();
                        ImGui::EndTable();
                        ImGui::End();
                        return;
                    }
                    ImGui::PopID();

                    key ++;
                } else {
                    ImGui::TableNextColumn();
                    ImGui::Text("File");

                    std::string name = item.path().stem().string();
                    std::string exts = item.path().extension().string();
                    ImGui::TableNextColumn();
                    ImGui::Text(name.c_str());

                    ImGui::TableNextColumn();
                    ImGui::Text(exts.c_str());

                    ImGui::TableNextColumn();
                    std::size_t size = std::filesystem::file_size(item.path());
                    ImGui::Text("%ld", size);

                    ImGui::TableNextColumn();
                }
            }   

            ImGui::EndTable();
        }
    ImGui::End();
}
