#pragma once

#include <vector>

#include "Entity.hpp"
#include "components/Camera.hpp"
#include "components/PointLight.hpp"
#include "components/DirectionalLight.hpp"
#include "components/SpotLight.hpp"

namespace mobagen {
  class Renderer {
  public:
    virtual ~Renderer();

    virtual void render(const Entity &scene, std::shared_ptr<Camera> activeCamera,
                        const std::vector<std::shared_ptr<PointLight>> &pointLights,
                        const std::vector<std::shared_ptr<DirectionalLight>> &directionalLights,
                        const std::vector<std::shared_ptr<SpotLight>> &spotLights) const = 0;
  };
}