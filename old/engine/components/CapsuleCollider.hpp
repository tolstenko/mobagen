#pragma once

#include "BaseCollider.hpp"

namespace mobagen {
  class CapsuleCollider : public BaseCollider {
  public:
    CapsuleCollider(float radius, float height, float mass);

    inline virtual const char *getType(void) { return "CAPSULE_COLLIDER"; };
  };
}