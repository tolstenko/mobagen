#pragma once

#include "Engine.hpp"
using namespace mobagen;

class SimpleBehaviour : public Component {
public:
  const char* getType() override{return "SimpleBehaviour";};
//  void updateInput(Input* input, double delta) override {};
  void update(Input *input, std::chrono::microseconds delta) override;
  void render(Shader* shader) override {};
  void registerWithEngine(Engine* engine) override {};
  void deregisterFromEngine(Engine* engine) override {};
  void onGUI(ImGuiContext* context) override;
};
