#include "SceneEditor.hpp"

#include <glm/gtc/matrix_transform.hpp>

#include <iostream>

void SceneEditor::leftClick(ImVec2 pos, ImVec2 size) {
    lastPos = pos;
    lastSize = size;
    leftClickRegistered = true;
}

SceneEditor::SceneEditor():
    Viewport(1920, 1080, "Editor"),
    cameraController(glm::vec3(0, 0, 0)),
    ray(btVector3(0, 0, 0), btVector3(0, 0, 0))
{
    Viewport::setClearColor(glm::vec3(.25, .25, .25));
}

SceneEditor::~SceneEditor() {

}

const FreecamController& SceneEditor::getCameraController() {
    return cameraController;
}

void SceneEditor::render(ImGuiWindowFlags extraFlags, GLFWwindow* window, float deltaTime, std::shared_ptr<Shape>& selectedObject) {
    if (!open) return;
    // 3D Math stuff...
    glm::mat4 viewMatrix = cameraController.getViewMatrix();
    glm::vec2 framebufferSize = Viewport::getSize();
    glm::mat4 projectionMatrix = glm::perspective(glm::radians(60.0f), framebufferSize.x / framebufferSize.y, 0.1f, 10000.0f);

    glm::mat4 viewProjection = projectionMatrix * viewMatrix;
        
    // Camera controller logic
    cameraController.step(window, deltaTime);

    if (scene == nullptr) return;

    Viewport::setupRender();
        scene->sceneEditorRender(viewProjection);
    Viewport::endRender();

    Viewport::renderWindow(extraFlags);

    if (leftClickRegistered) {
        float x = (2.0f * lastPos.x) / lastSize.x - 1.0f;
        float y = 1.0f - (2.0f * lastPos.y) / lastSize.y;
        float z = 1.0f;

        glm::vec3 ray_nds = glm::vec3(x, y, z);
        glm::vec4 ray_clip = glm::vec4(ray_nds.x, ray_nds.y, -1.0, 1.0);

        glm::vec4 ray_eye = glm::inverse(projectionMatrix) * ray_clip;
        ray_eye = glm::vec4(ray_eye.x, ray_eye.y, -1.0, 0.0);

        glm::vec4 ray_wor4 = (glm::inverse(viewMatrix) * ray_eye);
        glm::vec3 ray_wor = glm::vec3(ray_wor4.x, ray_wor4.y, ray_wor4.z);
        // don't forget to normalise the vector at some point
        ray_wor = glm::normalize(ray_wor);

        glm::vec3 cameraPosGLM = cameraController.getCamera().pos;

        btVector3 rayStart = btVector3(cameraPosGLM.x, cameraPosGLM.y, cameraPosGLM.z);
        btVector3  rayEnd   = rayStart + btVector3(ray_wor.x, ray_wor.y, ray_wor.z) * 100;

        ray = btCollisionWorld::ClosestRayResultCallback(rayStart, rayEnd);

        scene->getPhysicsWorld()->rayTest(rayStart, rayEnd, ray);
        if(ray.hasHit()) {
            const btRigidBody* hitObj = btRigidBody::upcast(ray.m_collisionObject);
            for (auto& obj : scene->getObjects()) {
                if (obj->getRigidbody() == hitObj) {
                    selectedObject = obj;
                    
                    break;
                }    
            }
        }
        leftClickRegistered = false;
    }
}

void SceneEditor::setScene(std::shared_ptr<Scene> _scene) {
    scene = _scene;
}