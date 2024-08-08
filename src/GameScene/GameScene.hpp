#pragma once 

#include <btBulletCollisionCommon.h>
#include <btBulletDynamicsCommon.h>

#include <vector>
#include <memory>

#include <glm/glm.hpp>

#include "MyUtility/Shapes/Cube/Cube.hpp"
#include "MyUtility/Shapes/Sphere/Sphere.hpp"

#include "MyUtility/ShapeRenderer/ShapeRenderer.hpp"

class GameScene {
private:
    struct ModelRenderingInfo {
        std::unique_ptr<Cube::RenderInfo> cubeRenderInfo;
        std::unique_ptr<Sphere::RenderInfo> sphereRenderInfo;
    };

    btDefaultCollisionConfiguration* collisionConfiguration;
	btCollisionDispatcher* dispatcher;
	btBroadphaseInterface* overlappingPairCache;
	btSequentialImpulseConstraintSolver* solver;

	btDiscreteDynamicsWorld* dynamicsWorld;

    ModelRenderingInfo renderInfo;
    std::vector<std::shared_ptr<Shape>> objects;

    std::string sceneName;


public:
    GameScene(std::string sceneName);
    ~GameScene();

    void sceneEditorRender(glm::mat4 viewProjection);

    std::string getSceneName() const;

    std::vector<std::shared_ptr<Shape>>& getObjects();
};