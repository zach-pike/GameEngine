#pragma once 

#include "imgui/imgui.h"

#include <memory>
#include "GameScene/GameScene.hpp"

class SceneExplorer {
private:
    std::shared_ptr<GameScene> currentScene;
public:
    SceneExplorer();
    ~SceneExplorer();

    void setScene(std::shared_ptr<GameScene>);

    void render(ImGuiWindowFlags extraFlags);
};