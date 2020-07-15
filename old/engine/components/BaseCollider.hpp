#pragma once

#include "Component.hpp"

#include <btBulletDynamicsCommon.h>

namespace mobagen {
  class BaseCollider : public Component {
  public:
    BaseCollider(btCollisionShape *shape, float mass);

    virtual ~BaseCollider(void);

    virtual void registerWithEngine(Engine *engine);

    virtual void deregisterFromEngine(Engine *engine);

    virtual void update(Input *input, std::chrono::microseconds delta);

    inline virtual const char *getType(void) { return "BASE_COLLIDER"; };

    void applyCentralImpulse(const glm::vec3 &impulse);

    btRigidBody* getRigidBody();

  private:
    btRigidBody *m_body;
    btDefaultMotionState *m_myMotionState;
    btCollisionShape *m_shape;
  };
}