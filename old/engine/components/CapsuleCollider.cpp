#include "CapsuleCollider.hpp"

namespace mobagen {
  CapsuleCollider::CapsuleCollider(float radius, float height, float mass) : BaseCollider(
      new btCapsuleShape(radius, height), mass) {
  }
}