#pragma once

#include <memory>

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "imgui/imgui.h"
#include <glm/glm.hpp>

#include "Utility/Camera/Camera.hpp"
#include "CameraProgram/CameraProgram.hpp"

class Viewport;

class FreecamController {
private:
    double lastMouseX, lastMouseY;
    Camera camera;

    bool isMouseLockedButtonPressed = false;

    bool isFirstStep = true;
    bool firstLockFrame = true;

    std::shared_ptr<CameraProgram> cameraProgram = nullptr;
    CameraProgram::CameraData      cameraProgramData = {  };

    void lockMouse(GLFWwindow* window);
    void unlockMouse(GLFWwindow* window);
public:
    bool isMouseLocked = false;
    FreecamController(glm::vec3 cameraPos);
    ~FreecamController();

    glm::mat4 getViewMatrix() const;
    const Camera& getCamera() const;

    void useProgram(std::shared_ptr<CameraProgram> program);

    void step(GLFWwindow* window, double deltaTime);
    void stepGrab(GLFWwindow* window, double deltaTime, const Viewport* vpt);
};