#include "GameScene.hpp"

#include <iostream>

GameScene::GameScene(std::string _sceneName):
    sceneName(_sceneName)
{
    collisionConfiguration = new btDefaultCollisionConfiguration();
	dispatcher = new btCollisionDispatcher(collisionConfiguration);
	overlappingPairCache = new btDbvtBroadphase();
	solver = new btSequentialImpulseConstraintSolver;

	dynamicsWorld = new btDiscreteDynamicsWorld(dispatcher, overlappingPairCache, solver, collisionConfiguration);

	dynamicsWorld->setGravity(btVector3(0, -9.81, 0));

    // Setup render
    renderInfo.sphereRenderInfo = Sphere::setupRender();
    renderInfo.cubeRenderInfo   = Cube::setupRender();

    objects.push_back(std::make_unique<Cube>(dynamicsWorld, btVector3(1000, 1, 1000), 0, btVector3(0, -10, 0)));
}

GameScene::~GameScene() {
    Cube::cleanupRender(renderInfo.cubeRenderInfo);
    Sphere::cleanupRender(renderInfo.sphereRenderInfo);

    delete dynamicsWorld;
    delete solver;
    delete overlappingPairCache;
    delete dispatcher;
    delete collisionConfiguration;
}

void GameScene::sceneEditorRender(glm::mat4 viewProjection) {
    for (int j=0; j<Shape::NTypes; j++) {
        switch((Shape::ModelType)j) {
            case Shape::ModelType::Sphere: Sphere::startRender(renderInfo.sphereRenderInfo); break;
            case Shape::ModelType::Cube: Cube::startRender(renderInfo.cubeRenderInfo); break;
        }

        for (auto& obj : objects) {
            btTransform transform;
            obj->getRigidbody()->getMotionState()->getWorldTransform(transform);

            glm::mat4 modelMatrix;
            transform.getOpenGLMatrix(&modelMatrix[0][0]);

            switch (obj->getObjectType()) {
                case Shape::ModelType::Sphere: {
                    std::shared_ptr<Sphere> sphere = std::dynamic_pointer_cast<Sphere>(obj);
                    Sphere::render(renderInfo.sphereRenderInfo, viewProjection, modelMatrix, sphere);
                } break;

                case Shape::ModelType::Cube: {
                    std::shared_ptr<Cube> cube = std::dynamic_pointer_cast<Cube>(obj);
                    Cube::render(renderInfo.cubeRenderInfo, viewProjection, modelMatrix, cube);
                } break;

                case Shape::ModelType::Mesh: {
                    std::cerr << "Mesh not implemented yet\n";
                    std::exit(1);
                } break;
            }
        }

        switch((Shape::ModelType)j) {
            case Shape::ModelType::Sphere: Sphere::endRender(renderInfo.sphereRenderInfo); break;
            case Shape::ModelType::Cube: Cube::endRender(renderInfo.cubeRenderInfo); break;
        }
    }   
}

std::string GameScene::getSceneName() const {
    return sceneName;
}

std::vector<std::shared_ptr<Shape>>& GameScene::getObjects() {
    return objects;
}