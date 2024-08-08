#pragma once

#include <btBulletDynamicsCommon.h>

class Shape {
public:
    virtual btRigidBody* getRigidbody() = 0;
    virtual btCollisionShape* getCollisionShape() = 0;
};