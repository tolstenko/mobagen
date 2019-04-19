#pragma once
#include "Engine.hpp"
#include "Texture.hpp"
//#include <boost/filesystem.hpp>
//#include <boost/foreach.hpp>
using namespace mobagen;

class StartPage : public Component
{
public:
  StartPage();
  ~StartPage() = default;;
  const char* getType() override;
  void update(Input *input, std::chrono::microseconds delta) override;
  void render(Shader* shader) override {};
  void registerWithEngine(Engine* engine) override {};
  void deregisterFromEngine(Engine* engine) override {};
  void onGUI(ImGuiContext* context) override;




  std::shared_ptr<Texture> normalTexture;
  std::shared_ptr<Texture> specularTexture;

  std::shared_ptr<Entity> rootScene;
private:

};
