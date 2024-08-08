#include "Cube.hpp"

#include "MyUtility/ShaderLoaders/VertexFragment/VertexFragment.hpp"

#include <glm/gtc/matrix_transform.hpp>

glm::vec3 cubeVertexData[] = {
    glm::vec3(-1.0f,-1.0f,-1.0f),
	glm::vec3(-1.0f,-1.0f, 1.0f),
	glm::vec3(-1.0f, 1.0f, 1.0f),
	glm::vec3( 1.0f, 1.0f,-1.0f),
	glm::vec3(-1.0f,-1.0f,-1.0f),
	glm::vec3(-1.0f, 1.0f,-1.0f),
	glm::vec3( 1.0f,-1.0f, 1.0f),
	glm::vec3(-1.0f,-1.0f,-1.0f),
	glm::vec3( 1.0f,-1.0f,-1.0f),
	glm::vec3( 1.0f, 1.0f,-1.0f),
	glm::vec3( 1.0f,-1.0f,-1.0f),
	glm::vec3(-1.0f,-1.0f,-1.0f),
	glm::vec3(-1.0f,-1.0f,-1.0f),
	glm::vec3(-1.0f, 1.0f, 1.0f),
	glm::vec3(-1.0f, 1.0f,-1.0f),
	glm::vec3( 1.0f,-1.0f, 1.0f),
	glm::vec3(-1.0f,-1.0f, 1.0f),
	glm::vec3(-1.0f,-1.0f,-1.0f),
	glm::vec3(-1.0f, 1.0f, 1.0f),
	glm::vec3(-1.0f,-1.0f, 1.0f),
	glm::vec3( 1.0f,-1.0f, 1.0f),
	glm::vec3( 1.0f, 1.0f, 1.0f),
	glm::vec3( 1.0f,-1.0f,-1.0f),
	glm::vec3( 1.0f, 1.0f,-1.0f),
	glm::vec3( 1.0f,-1.0f,-1.0f),
	glm::vec3( 1.0f, 1.0f, 1.0f),
	glm::vec3( 1.0f,-1.0f, 1.0f),
	glm::vec3( 1.0f, 1.0f, 1.0f),
	glm::vec3( 1.0f, 1.0f,-1.0f),
	glm::vec3(-1.0f, 1.0f,-1.0f),
	glm::vec3( 1.0f, 1.0f, 1.0f),
	glm::vec3(-1.0f, 1.0f,-1.0f),
	glm::vec3(-1.0f, 1.0f, 1.0f),
	glm::vec3( 1.0f, 1.0f, 1.0f),
	glm::vec3(-1.0f, 1.0f, 1.0f),
	glm::vec3( 1.0f,-1.0f, 1.0f)
};

glm::vec2 cubeUVData[] = { 
	glm::vec2(0.000059f, 1.0f-0.000004f), 
	glm::vec2(0.000103f, 1.0f-0.336048f), 
	glm::vec2(0.335973f, 1.0f-0.335903f), 
	glm::vec2(1.000023f, 1.0f-0.000013f), 
	glm::vec2(0.667979f, 1.0f-0.335851f), 
	glm::vec2(0.999958f, 1.0f-0.336064f), 
	glm::vec2(0.667979f, 1.0f-0.335851f), 
	glm::vec2(0.336024f, 1.0f-0.671877f), 
	glm::vec2(0.667969f, 1.0f-0.671889f), 
	glm::vec2(1.000023f, 1.0f-0.000013f), 
	glm::vec2(0.668104f, 1.0f-0.000013f), 
	glm::vec2(0.667979f, 1.0f-0.335851f), 
	glm::vec2(0.000059f, 1.0f-0.000004f), 
	glm::vec2(0.335973f, 1.0f-0.335903f), 
	glm::vec2(0.336098f, 1.0f-0.000071f), 
	glm::vec2(0.667979f, 1.0f-0.335851f), 
	glm::vec2(0.335973f, 1.0f-0.335903f), 
	glm::vec2(0.336024f, 1.0f-0.671877f), 
	glm::vec2(1.000004f, 1.0f-0.671847f), 
	glm::vec2(0.999958f, 1.0f-0.336064f), 
	glm::vec2(0.667979f, 1.0f-0.335851f), 
	glm::vec2(0.668104f, 1.0f-0.000013f), 
	glm::vec2(0.335973f, 1.0f-0.335903f), 
	glm::vec2(0.667979f, 1.0f-0.335851f), 
	glm::vec2(0.335973f, 1.0f-0.335903f), 
	glm::vec2(0.668104f, 1.0f-0.000013f), 
	glm::vec2(0.336098f, 1.0f-0.000071f), 
	glm::vec2(0.000103f, 1.0f-0.336048f), 
	glm::vec2(0.000004f, 1.0f-0.671870f), 
	glm::vec2(0.336024f, 1.0f-0.671877f), 
	glm::vec2(0.000103f, 1.0f-0.336048f), 
	glm::vec2(0.336024f, 1.0f-0.671877f), 
	glm::vec2(0.335973f, 1.0f-0.335903f), 
	glm::vec2(0.667969f, 1.0f-0.671889f), 
	glm::vec2(1.000004f, 1.0f-0.671847f), 
	glm::vec2(0.667979f, 1.0f-0.335851f)
};

static float randScalar() {
    const int v = 1000;

    int m = rand() % v;

    return (float)m / (float)v;
}

std::unique_ptr<Cube::RenderInfo> Cube::setupRender() {
    auto info = std::make_unique<RenderInfo>();

    info->shader = loadVertexFragmentShader("./shader/cube/");
    info->shader->use();

    info->uniforms.mvp = info->shader->getUniformLocation("MVP");
    info->uniforms.texture = info->shader->getUniformLocation("myTexture");
    info->uniforms.color = info->shader->getUniformLocation("inColor");

    info->shader->unbind();

    info->vertexBuffer.bufferData(cubeVertexData);
    info->uvBuffer.bufferData(cubeUVData);

    return info;
}

void Cube::cleanupRender(std::unique_ptr<RenderInfo>&) {
    // Nothing here
}

void Cube::startRender(std::unique_ptr<RenderInfo>& info) {
    glEnableVertexAttribArray(0);
    glEnableVertexAttribArray(1);

    info->shader->use();

    glBindBuffer(GL_ARRAY_BUFFER, info->vertexBuffer.getBufferId());
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, nullptr);

    glBindBuffer(GL_ARRAY_BUFFER, info->uvBuffer.getBufferId());
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 0, nullptr);
}

void Cube::render(std::unique_ptr<RenderInfo>& info, glm::mat4 viewProj, glm::mat4 modelMatrix, std::shared_ptr<Cube>& cube) {
    auto size = cube->getSize();
    modelMatrix = glm::scale(modelMatrix, glm::vec3(size.x(), size.y(), size.z()));

    glm::mat4 MVP = viewProj * modelMatrix;
    glm::vec3 color = cube->getColor();

    glUniform3fv(info->uniforms.color, 1, &color[0]);
    glUniformMatrix4fv(info->uniforms.mvp, 1, GL_FALSE, &MVP[0][0]);

    glDrawArrays(GL_TRIANGLES, 0, 36);
}

void Cube::endRender(std::unique_ptr<RenderInfo>& info) {
    glDisableVertexAttribArray(0);
    glDisableVertexAttribArray(1);

    info->shader->unbind();
}

Cube::Cube(btDiscreteDynamicsWorld* _world, btVector3 _size, float _mass, btVector3 position):
    world(_world),
    size(_size),
    mass(_mass)
{
    btTransform transfprm;
	transfprm.setIdentity();
	transfprm.setOrigin(position);
    motionState = new btDefaultMotionState(transfprm);

    shape = new btBoxShape(btVector3(.5, .5, .5) * size);

    btVector3 localInertia(0, 0, 0);
    shape->calculateLocalInertia(mass, localInertia);

	btRigidBody::btRigidBodyConstructionInfo rbInfo(mass, motionState, shape, localInertia);
	body = new btRigidBody(rbInfo);

    world->addRigidBody(body);

    color = glm::vec3(randScalar(), randScalar(), randScalar());
}

Cube::~Cube() {
    world->removeRigidBody(body);

    delete motionState;
    delete shape;
    delete body;
}

btRigidBody* Cube::getRigidbody() {
    return body;
}

btCollisionShape* Cube::getCollisionShape() {
	return shape;
}

Shape::ModelType Cube::getObjectType() {
	return Shape::ModelType::Cube;
}

btVector3 Cube::getSize() {
    return size;
}

glm::vec3 Cube::getColor() {
    return color;
}