#pragma once

#include "Entity.hpp"
#include "Ray.hpp"

#include <vector>
#include <chrono>

#include <btBulletDynamicsCommon.h>

namespace mobagen {
  class PhysicsManager {
  public:
    PhysicsManager(void);

    ~PhysicsManager(void);

    void registerCollider(btRigidBody *rigidBody);

    void deregisterCollider(btRigidBody *rigidBody);

    void tick(std::chrono::microseconds delta);

    Entity *pick(Ray *ray) const;

    glm::vec3 getGravity();

    void setGravity(glm::vec3);

  private:
    btDefaultCollisionConfiguration *m_collisionConfiguration;
    btCollisionDispatcher *m_dispatcher;
    btBroadphaseInterface *m_overlappingPairCache;
    btSequentialImpulseConstraintSolver *m_solver;
    btDiscreteDynamicsWorld *m_dynamicsWorld;
  };
}