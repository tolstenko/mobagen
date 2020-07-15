#pragma once

#include "BaseCollider.hpp"

namespace mobagen {
  class BoxCollider : public BaseCollider {
  public:
    BoxCollider(const glm::vec3 &size, float mass);

    inline virtual const char *getType(void) { return "BOX_COLLIDER"; };
  };
}