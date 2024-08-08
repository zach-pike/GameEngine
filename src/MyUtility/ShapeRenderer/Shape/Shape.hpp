#pragma once

#include <btBulletDynamicsCommon.h>

#include <cstdint>

class Shape {
public:
    enum class ModelType : std::uint8_t {
        Sphere = 0,
        Cube   = 1,
        Mesh   = 2,
    };

    static const char* getModelTypeString(ModelType type);

    static const int NTypes = 3;

    virtual btRigidBody* getRigidbody() = 0;
    virtual btCollisionShape* getCollisionShape() = 0;
    virtual ModelType getObjectType() = 0;
};