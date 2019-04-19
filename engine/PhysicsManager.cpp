#include "PhysicsManager.hpp"

#include <glm/gtx/norm.hpp>

#include <algorithm>

namespace mobagen {
  PhysicsManager::PhysicsManager(void) {
    m_collisionConfiguration = new btDefaultCollisionConfiguration();
    m_dispatcher = new btCollisionDispatcher(m_collisionConfiguration);
    m_overlappingPairCache = new btDbvtBroadphase();
    m_solver = new btSequentialImpulseConstraintSolver;
    m_dynamicsWorld = new btDiscreteDynamicsWorld(m_dispatcher, m_overlappingPairCache, m_solver,
                                                  m_collisionConfiguration);

    m_dynamicsWorld->setGravity(btVector3(0, -9.8, 0));
  }

  PhysicsManager::~PhysicsManager(void) {
    delete m_dynamicsWorld;
    delete m_solver;
    delete m_overlappingPairCache;
    delete m_dispatcher;
    delete m_collisionConfiguration;
  }

  void PhysicsManager::registerCollider(btRigidBody *rigidBody) {
    m_dynamicsWorld->addRigidBody(rigidBody);
  }

  void PhysicsManager::deregisterCollider(btRigidBody *rigidBody) {
    m_dynamicsWorld->removeRigidBody(rigidBody);
  }

  void PhysicsManager::tick(std::chrono::microseconds delta) {
    m_dynamicsWorld->stepSimulation(std::chrono::duration_cast<std::chrono::duration<float>>(delta).count(),0,1.0f/360);
  }

  Entity *PhysicsManager::pick(Ray *ray) const {
    auto position = ray->getPosition();
    auto positionVec = btVector3(position.x, position.y, position.z);

    auto endPosition = ray->getEndPosition(10000.f);
    auto endPositionVec = btVector3(endPosition.x, endPosition.y, endPosition.z);

    btCollisionWorld::ClosestRayResultCallback rayCallback(positionVec, endPositionVec);

    m_dynamicsWorld->rayTest(positionVec, endPositionVec, rayCallback);

    if (rayCallback.hasHit()) {
      return (Entity *) rayCallback.m_collisionObject->getUserPointer();
    } else {
      return nullptr;
    }
  }

  glm::vec3 PhysicsManager::getGravity() {
    auto g = m_dynamicsWorld->getGravity();
    return glm::vec3(g.x(),g.y(),g.z());
  }

  void PhysicsManager::setGravity(glm::vec3 g) {
    m_dynamicsWorld->setGravity(btVector3(g.x, g.y, g.z));
  }
}