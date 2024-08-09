#include "SceneEditor.hpp"

#include <glm/gtc/matrix_transform.hpp>

SceneEditor::SceneEditor():
    Viewport(1920, 1080, "Editor"),
    cameraController(glm::vec3(0, 0, 0))
{
    Viewport::setClearColor(glm::vec3(.25, .25, .25));
}

SceneEditor::~SceneEditor() {

}

const FreecamController& SceneEditor::getCameraController() {
    return cameraController;
}

void SceneEditor::render(ImGuiWindowFlags extraFlags, GLFWwindow* window, float deltaTime) {
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
}

void SceneEditor::setScene(std::shared_ptr<GameScene> _scene) {
    scene = _scene;
}