#pragma once

// #include <glfw/glfw3.h>

#include <memory>

#include "MyUtility/CameraControllers/FreecamController/FreecamController.hpp"

#include "GameScene/GameScene.hpp"
#include "Viewport/Viewport.hpp"

struct GLFWwindow;

class SceneEditor : public Viewport {
public:
    bool open = true;
private:
    std::shared_ptr<GameScene> scene;

    FreecamController cameraController;
public:
    SceneEditor();
    ~SceneEditor();

    const FreecamController& getCameraController();
    void render(ImGuiWindowFlags extraFlags, GLFWwindow* window, float deltaTime);

    void setScene(std::shared_ptr<GameScene>);
};