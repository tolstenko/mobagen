#include "SphereCollider.hpp"

namespace mobagen {
  SphereCollider::SphereCollider(float size, float mass) : BaseCollider(new btSphereShape(size), mass) {
  }
}