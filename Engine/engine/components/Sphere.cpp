#include "Sphere.hpp"
#include "Engine.hpp"

namespace mobagen {
  Sphere::Sphere(float radius) : Component() {
    m_radius = radius;
    setProperty("radius", FLOAT, &m_radius, 0, 10);
  }

  void Sphere::registerWithEngine(Engine *engine) {
    engine->getPhysicsManager()->registerCollider(shared_from_this());
  }

  void Sphere::deregisterFromEngine(Engine *engine) {
    engine->getPhysicsManager()->deregisterCollider(shared_from_this());
  }

  float Sphere::getRadius(void) const {
    return m_radius;
  }
}