#pragma once

// #include <glfw/glfw3.h>

#include <memory>

#include "MyUtility/CameraControllers/FreecamController/FreecamController.hpp"

#include "Scene/Scene.hpp"
#include "Viewport/Viewport.hpp"

#include "imgui/imgui.h"

struct GLFWwindow;

class SceneEditor : public Viewport {
public:
    bool open = true;
private:
    std::shared_ptr<Scene> scene;

    FreecamController cameraController;

    bool leftClickRegistered = false;
    ImVec2 lastSize, lastPos;

    btCollisionWorld::ClosestRayResultCallback ray;
protected:
    void leftClick(ImVec2 pos, ImVec2 size);
public:
    SceneEditor();
    ~SceneEditor();

    const FreecamController& getCameraController();
    void render(ImGuiWindowFlags extraFlags, GLFWwindow* window, float deltaTime, std::shared_ptr<Shape>& selectedObject);

    void setScene(std::shared_ptr<Scene>);
};