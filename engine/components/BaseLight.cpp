#include "BaseLight.hpp"

namespace mobagen {
  BaseLight::BaseLight(glm::vec3 color, float intensity) {
    m_color = color;
    m_intensity = intensity;

    setProperty("color", COLORPROPERTY, &m_color.x, 0, 1);
    setProperty("intensity", FLOATPROPERTY, &m_intensity, 0, 100);
  }

  BaseLight::~BaseLight(void) {
  }

  glm::vec3 BaseLight::getColor(void) const {
    return m_color;
  }

  float BaseLight::getIntensity(void) const {
    return m_intensity;
  }
}