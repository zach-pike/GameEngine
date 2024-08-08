#pragma once 

#include "Utility/GL/Texture/Texture.hpp"

#include "imgui/imgui.h"

#include <filesystem>

namespace fs = std::filesystem;

class AssetExplorer {
private:
    Texture folderTexture;
    Texture fileTexture;

    fs::path currentPath;


public:
    AssetExplorer();
    ~AssetExplorer();

    void render(ImGuiWindowFlags extraWindowFlags);
};