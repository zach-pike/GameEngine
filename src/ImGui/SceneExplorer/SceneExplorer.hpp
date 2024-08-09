#pragma once 

#include "imgui/imgui.h"

#include <memory>
#include "Scene/Scene.hpp"

class SceneExplorer {
public:
    bool open = true;
private:
    std::shared_ptr<Scene> currentScene;
public:
    SceneExplorer();
    ~SceneExplorer();

    void setScene(std::shared_ptr<Scene>);

    void render(ImGuiWindowFlags extraFlags, std::shared_ptr<Shape>& selectedObject);
};