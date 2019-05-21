#pragma once

#include <memory>
#include <chrono>

#include "Input.hpp"
#include "Shader.hpp"
#include "Entity.hpp"
#include "Transform.hpp"
#include <imgui.h>
#include "Object.hpp"


namespace mobagen {
  class Engine;

  enum PropertyType {
    FLOATPROPERTY,
    FLOAT3PROPERTY,
    BOOLEANPROPERTY,
    ANGLEPROPERTY,
    COLORPROPERTY
  };

  struct Property {
    PropertyType type;
    void *p;
    float min;
    float max;
  };

  class Component {
  public:

    virtual ~Component(void) {};

    virtual void update(Input *input, std::chrono::microseconds delta) {};

    virtual void render(Shader *shader) {};

    virtual void registerWithEngine(Engine *engine) {};

    virtual void deregisterFromEngine(Engine *engine) {};

    virtual void onGUI(ImGuiContext *context) {};

    virtual const char *getType(void) = 0;

    void setProperty(const char *name, PropertyType type, void *p, float min, float max);

    void setProperty(const char *name, PropertyType type, void *p);

    void setParent(Entity *parentEntity);

    Entity *getParent(void) const;

    Transform &getTransform(void) const;

    std::map<const char *, Property> m_properties;

    // TODO: Remove this
    Engine *getEngine();

    // TODO: Remove this
    std::chrono::microseconds getDeltaTime();

  protected:
    Entity *m_parentEntity;
  };
}