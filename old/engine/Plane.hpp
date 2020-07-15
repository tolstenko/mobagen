#pragma once

#include "Mesh.hpp"

namespace mobagen {
  class Plane {
  public:
    Plane(void);

    ~Plane(void);

    static std::shared_ptr<Mesh> getMesh(void);
  };
}