#include "BoxCollider.hpp"

namespace mobagen {
  BoxCollider::BoxCollider(const glm::vec3 &size, float mass) : BaseCollider(
      new btBoxShape(btVector3(size.x, size.y, size.z)), mass) {
  }
}