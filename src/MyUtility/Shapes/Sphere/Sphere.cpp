#include "Sphere.hpp"

#include "MyUtility/ShaderLoaders/Tessellation/Tessellation.hpp"

#include <glm/glm.hpp>

static glm::vec3 faceVertexData[] = {
    glm::vec3( 1.0f,-1.0f, -1.0f),
	glm::vec3(-1.0f,-1.0f, -1.0f),
	glm::vec3( 1.0f, 1.0f, -1.0f),
	glm::vec3(-1.0f, 1.0f, -1.0f),
    glm::vec3(-1.0f,-1.0f, 1.0f),
	glm::vec3( 1.0f,-1.0f, 1.0f),
	glm::vec3(-1.0f, 1.0f, 1.0f),
	glm::vec3( 1.0f, 1.0f, 1.0f),
    glm::vec3(-1.0f, -1.0f,-1.0f),
    glm::vec3(-1.0f, -1.0f, 1.0f),
    glm::vec3(-1.0f,  1.0f,-1.0f),
    glm::vec3(-1.0f,  1.0f, 1.0f),
    glm::vec3(1.0f, -1.0f, 1.0f),
    glm::vec3(1.0f, -1.0f,-1.0f),
    glm::vec3(1.0f,  1.0f, 1.0f),
    glm::vec3(1.0f,  1.0f,-1.0f),
    glm::vec3( 1.0f, 1.f,-1.0f),
    glm::vec3(-1.0f, 1.f,-1.0f),
    glm::vec3( 1.0f, 1.f, 1.0f),
    glm::vec3(-1.0f, 1.f, 1.0f),
    glm::vec3(-1.0f,-1.f,-1.0f),
    glm::vec3( 1.0f,-1.f,-1.0f),
    glm::vec3(-1.0f,-1.f, 1.0f),
    glm::vec3( 1.0f,-1.f, 1.0f),
};

std::unique_ptr<Sphere::RenderInfo> Sphere::setupRender() {
    auto info = std::make_unique<RenderInfo>();

    info->shader = loadTessellationShader("./shader/sphere/");
    info->shader->use();

    info->uniforms.mvp = info->shader->getUniformLocation("MVP");
    info->uniforms.texture = info->shader->getUniformLocation("myTexture");
    info->uniforms.quality = info->shader->getUniformLocation("quality");
    info->uniforms.scale = info->shader->getUniformLocation("scale");

    glUniform1f(info->uniforms.quality, 10.f);

    info->shader->unbind();

    info->vertexBuffer.bufferData(faceVertexData);
    info->texture.loadFromFilePath("resources/wapple.png");

    return info;
}

void Sphere::cleanupRender(std::unique_ptr<RenderInfo>& renderInfo) {
    // Not much to do here
}

void Sphere::startRender(std::unique_ptr<RenderInfo>& info) {
    glEnableVertexAttribArray(0);

    info->shader->use();
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, info->texture.getTextureId());
    glUniform1i(info->uniforms.texture, 0);

    glPatchParameteri(GL_PATCH_VERTICES, 4);

    glBindBuffer(GL_ARRAY_BUFFER, info->vertexBuffer.getBufferId());
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, nullptr);
}

void Sphere::render(std::unique_ptr<RenderInfo>& info, glm::mat4 viewProj, glm::mat4 modelMatrix, std::shared_ptr<Sphere>& sphere) {
    glm::mat4 MVP = viewProj * modelMatrix;

    glUniformMatrix4fv(info->uniforms.mvp, 1, GL_FALSE, &MVP[0][0]);
    glUniform1f(info->uniforms.scale, sphere->getRadius());
    glDrawArrays(GL_PATCHES, 0, 24);
}

void Sphere::endRender(std::unique_ptr<RenderInfo>& info) {
    glDisableVertexAttribArray(0);
    
    info->shader->unbind();
}

Sphere::Sphere(btDiscreteDynamicsWorld* _world, float _rad, float _mass, btVector3 position):
    radius(_rad),
    mass(_mass),
    world(_world)
{
    btTransform transfprm;
	transfprm.setIdentity();
	transfprm.setOrigin(position);
    motionState = new btDefaultMotionState(transfprm);

    shape = new btSphereShape(radius);

    btVector3 localInertia(0, 0, 0);
    shape->calculateLocalInertia(mass, localInertia);

	btRigidBody::btRigidBodyConstructionInfo rbInfo(mass, motionState, shape, localInertia);
	body = new btRigidBody(rbInfo);

    world->addRigidBody(body);
}

Sphere::~Sphere() {
    world->removeRigidBody(body);

    delete motionState;
    delete shape;
    delete body;
}

btRigidBody* Sphere::getRigidbody() {
    return body;
}

btCollisionShape* Sphere::getCollisionShape() {
    return shape;
}

Shape::ModelType Sphere::getObjectType() {
    return Shape::ModelType::Sphere;
}

float Sphere::getRadius() {
    return radius;
}