#pragma once

#include <memory>
#include <vector>

#include <btBulletDynamicsCommon.h>

#include <glm/glm.hpp>

template <class T>
class ShapeRenderer {
private:
    std::unique_ptr<typename T::RenderInfo> renderInfo;
public:
    std::vector<std::unique_ptr<T>> shapes;

    ShapeRenderer() {
        renderInfo = T::setupRender();
    }
    ~ShapeRenderer() {
        T::cleanupRender(renderInfo);
    }

    void render(glm::mat4 viewProjection) {
        T::startRender(renderInfo);

        for (auto& shape : shapes) {
            btTransform transform;
            shape->getRigidbody()->getMotionState()->getWorldTransform(transform);

            glm::mat4 modelMatrix;
            transform.getOpenGLMatrix(&modelMatrix[0][0]);

            T::render(renderInfo, viewProjection, modelMatrix, shape);
        }

        T::endRender(renderInfo);
    }
};