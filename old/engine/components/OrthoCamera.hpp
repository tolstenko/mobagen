#pragma once

#include "Camera.hpp"

#include <glm/glm.hpp>

namespace mobagen {
  class OrthoCamera : public Camera {
  public:
    OrthoCamera(float aspect, float scale, float zNear, float zFar);

    virtual glm::mat4 getProjectionMatrix(void) const;

    inline virtual const char *getType(void) { return "ORTHO_CAMERA"; }

  private:
    float m_scale, m_aspect, m_zNear, m_zFar;
  };
}