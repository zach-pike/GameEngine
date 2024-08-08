#pragma once

#include "glad/glad.h"
#include <GLFW/glfw3.h>

#include "Utility/Camera/Camera.hpp"

#include <glm/glm.hpp>

#include <btBulletCollisionCommon.h>
#include <btBulletDynamicsCommon.h>

class PlayerController {
private:
    double lastMouseX, lastMouseY;
    Camera camera;
    bool isFirstStep = true;
    bool isMouseLockedButtonPressed = false;

    bool jumpPressed = false;

    btDynamicsWorld*  world;
    btMotionState*    motionState;
    btCollisionShape* shape;
    btRigidBody*      body;

    void lockMouse(GLFWwindow* window);
    void unlockMouse(GLFWwindow* window);
public:
    bool isMouseLocked = true;
    PlayerController(btDynamicsWorld* world, glm::vec3 worldPosition);
    ~PlayerController();

    btRigidBody* getRigidbody();

    const Camera& getCamera() const;

    void step(GLFWwindow* window, float deltaTime);

    void render(GLuint mvp, glm::mat4 viewProj);
};