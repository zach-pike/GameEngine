#pragma once

#include "MyUtility/ShapeRenderer/Shape/Shape.hpp"

#include <glm/glm.hpp>

#include <btBulletDynamicsCommon.h>
#include <btBulletCollisionCommon.h>

#include <memory>

#include "Utility/GL/Buffer/Buffer.hpp"
#include "Utility/GL/ShaderProgram/ShaderProgram.hpp"

class Cube : public Shape {
public:
    struct RenderInfo {
        std::unique_ptr<ShaderProgram> shader;

        struct {
            GLuint mvp, texture, color;
        } uniforms;

        Buffer<glm::vec3> vertexBuffer;
        Buffer<glm::vec2> uvBuffer;
    };

    static std::unique_ptr<RenderInfo> setupRender();
    static void cleanupRender(std::unique_ptr<RenderInfo>&);

    static void startRender(std::unique_ptr<RenderInfo>&);
    static void render(std::unique_ptr<RenderInfo>&, glm::mat4 viewProj, glm::mat4 modelMatrix, std::shared_ptr<Cube>&);
    static void endRender(std::unique_ptr<RenderInfo>&);
private:
    btDiscreteDynamicsWorld* world;

    btDefaultMotionState* motionState;
    btCollisionShape*     shape;
    btRigidBody*          body;

    glm::vec3             color;

    btVector3 size;
    float mass;
public:
    Cube(btDiscreteDynamicsWorld* world, btVector3 size, float mass, btVector3 position);
    ~Cube();

    btRigidBody* getRigidbody();
    btCollisionShape* getCollisionShape();
    Shape::ModelType getObjectType();

    btVector3 getSize();
    glm::vec3 getColor();
};