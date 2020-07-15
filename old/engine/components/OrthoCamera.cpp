#define GLM_FORCE_RADIANS
#include <glm/gtx/transform.hpp>

#include "OrthoCamera.hpp"

namespace mobagen {
  OrthoCamera::OrthoCamera(float aspect, float scale, float zNear, float zFar) {
    m_scale = scale;
    m_aspect = aspect;
    m_zNear = zNear;
    m_zFar = zFar;

    setProperty("scale", FLOATPROPERTY, &m_scale, 0, 200);
    setProperty("aspect", FLOATPROPERTY, &m_aspect, 0, 10);
    setProperty("zNear", FLOATPROPERTY, &m_zNear, 0, 1);
    setProperty("zFar", FLOATPROPERTY, &m_zFar, 0, 1000);
  }

  glm::mat4 OrthoCamera::getProjectionMatrix(void) const {
    return glm::ortho(-m_aspect * m_scale, m_aspect * m_scale, -1.0f * m_scale, 1.0f * m_scale, m_zNear, m_zFar);
  }
}