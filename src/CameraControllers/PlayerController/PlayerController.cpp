#include "PlayerController.hpp"

#include <iostream>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

PlayerController::PlayerController(btDynamicsWorld* _world, glm::vec3 worldPosition):
    camera(worldPosition, 0, 0),
    world(_world)
{
    btTransform transfprm;
	transfprm.setIdentity();
	transfprm.setOrigin(btVector3(worldPosition.x, worldPosition.y, worldPosition.z));
    motionState = new btDefaultMotionState(transfprm);

    float mass = 5;

    shape = new btBoxShape(btVector3(.5, .5, .5));

    btVector3 localInertia(0, 0, 0);
    shape->calculateLocalInertia(mass, localInertia);

	btRigidBody::btRigidBodyConstructionInfo rbInfo(mass, motionState, shape, localInertia);
	body = new btRigidBody(rbInfo);

    body->setFriction(7);
    body->setAngularFactor(0);
    body->setSleepingThresholds(0, 0);

    world->addRigidBody(body);
}

PlayerController::~PlayerController() {
    world->removeRigidBody(body);

    delete body;
    delete shape;
    delete motionState;
}

void PlayerController::render(GLuint mvp, glm::mat4 viewProj) {
    // glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

    btTransform tf;
    body->getMotionState()->getWorldTransform(tf);

    glm::mat4 modelMatrix;
    tf.getOpenGLMatrix(&modelMatrix[0][0]);
    modelMatrix = glm::scale(modelMatrix, glm::vec3(.5));

    glm::mat4 MVP = viewProj * modelMatrix;

    glUniformMatrix4fv(mvp, 1, GL_FALSE, &MVP[0][0]);
    glDrawArrays(GL_TRIANGLES, 0, 36);

    // glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
}

void PlayerController::lockMouse(GLFWwindow* window) {
    isMouseLocked = true;
    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
}

void PlayerController::unlockMouse(GLFWwindow* window) {
    isMouseLocked = false;
    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
}

const Camera& PlayerController::getCamera() const {
    return camera;
}

void PlayerController::step(GLFWwindow* window, float deltaTime) {
    const float mouseSens = .35f;
    const float moveSpeed = 25.f;

    if (isFirstStep) {
        if (isMouseLocked) glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

        glfwSetCursorPos(window, 0, 0);
        isFirstStep = false;
    }

    // Camera lock toggle key
    if (glfwGetKey(window, GLFW_KEY_R) == GLFW_PRESS) {
        if (isMouseLockedButtonPressed == false) {
            isMouseLockedButtonPressed = true;

            if (isMouseLocked) {
                unlockMouse(window);
            } else {
                // Stop jumping when relocking mouse
                glfwSetCursorPos(window, 0, 0);
                lastMouseX = 0;
                lastMouseY = 0;
                
                lockMouse(window);
            }
        }
    } else {
        isMouseLockedButtonPressed = false;
    }

    if (isMouseLocked) {
        double mousePosX, mousePosY;
        glfwGetCursorPos(window, &mousePosX, &mousePosY);

        double mouseDeltaX = mousePosX - lastMouseX;
        double mouseDeltaY = mousePosY - lastMouseY;

        mouseDeltaX *= deltaTime;
        mouseDeltaY *= deltaTime;

        lastMouseX = mousePosX;
        lastMouseY = mousePosY;

        camera.yaw += mouseDeltaX * mouseSens;

        // Lock the camera to almost all the way down and almost all the way up
        camera.pitch = std::min(1.5f*M_PI - .01, std::max((double)M_PI_2 + .01, camera.pitch + mouseDeltaY * mouseSens));
    }

    auto looking = camera.getLookingVector();
    auto moveVector = glm::normalize(glm::vec3(looking.x, 0, looking.z));

    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS) {
        body->applyCentralForce(btVector3(moveVector.x, moveVector.y, moveVector.z) * 300);
    }

    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS) {
        body->applyCentralForce(btVector3(moveVector.z, moveVector.y, -moveVector.x) * 300);
    }

    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS) {
        body->applyCentralForce(btVector3(-moveVector.z, moveVector.y, moveVector.x) * 300);
    }

    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS) {
        body->applyCentralForce(btVector3(moveVector.x, moveVector.y, moveVector.z) * -300);
    }

    if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS) {
        if (!jumpPressed) {
            body->applyCentralForce(btVector3(0, 230, 0));
            // jumpPressed = true;
        }
    } else {
        jumpPressed = false;
    }

    btVector3 vel = body->getLinearVelocity();
    
    if (vel.norm() > 100) {
        vel = vel.normalize() * 100;
    }
    
    body->setLinearVelocity(vel);

    btTransform tf;
    body->getMotionState()->getWorldTransform(tf);
    btVector3 pos = tf.getOrigin();
    camera.pos = glm::vec3(pos.x(), pos.y(), pos.z())+glm::vec3(0, 2, 0);
}

btRigidBody* PlayerController::getRigidbody() {
    return body;
}