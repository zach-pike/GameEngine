#pragma once

#include "MyUtility/ShapeRenderer/Shape/Shape.hpp"

#include <glm/glm.hpp>

#include <btBulletDynamicsCommon.h>
#include <btBulletCollisionCommon.h>

#include <memory>

#include "Utility/GL/ShaderProgram/ShaderProgram.hpp"
#include "Utility/GL/Buffer/Buffer.hpp"
#include "Utility/GL/Texture/Texture.hpp"

class Sphere : public Shape {
public:
    struct RenderInfo {
        std::unique_ptr<ShaderProgram> shader;

        struct {
            GLuint mvp, texture, quality, scale;
        } uniforms;

        Texture texture;
        Buffer<glm::vec3> vertexBuffer;
    };

    static std::unique_ptr<RenderInfo> setupRender();
    static void cleanupRender(std::unique_ptr<RenderInfo>&);

    static void startRender(std::unique_ptr<RenderInfo>&);
    static void render(std::unique_ptr<RenderInfo>&, glm::mat4 viewProj, glm::mat4 modelMatrix, std::shared_ptr<Sphere>&);
    static void endRender(std::unique_ptr<RenderInfo>&);
private:
    btDiscreteDynamicsWorld* world;

    btDefaultMotionState* motionState;
    btCollisionShape*     shape;
    btRigidBody*          body;

    float radius;
    float mass;
public:
    Sphere(btDiscreteDynamicsWorld* world, float radius, float mass, btVector3 position);
    ~Sphere();

    btRigidBody* getRigidbody();
    btCollisionShape* getCollisionShape();
    Shape::ModelType getObjectType();

    float getRadius();
};