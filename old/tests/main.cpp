#include "components/MeshRenderer.hpp"
#include "components/PerspectiveCamera.hpp"
#include "components/OrthoCamera.hpp"
#include "components/FreeMove.hpp"
#include "components/FreeLook.hpp"
#include "components/DirectionalLight.hpp"
#include "components/SpotLight.hpp"
#include "components/PointLight.hpp"
#include "components/SphereCollider.hpp"
#include "Plane.hpp"
#include "Mesh.hpp"
#include "Texture.hpp"
#include "Logger.hpp"
#include "MeshLoader.hpp"
#include "Engine.hpp"
#include <SDL_main.h>
#include <iostream>
#include <map>
#include <random>
#include <GameObject.hpp>
#include "GameScriptedBehaviourTest.hpp"

class DocEditor : public Game
{
public:
  virtual void init(GLManager *glManager);
  virtual void update(Input *input, std::chrono::microseconds delta);
};

void DocEditor::update(Input *input, std::chrono::microseconds delta)
{
  Game::update(input, delta);
  //log_info("%llu",GameObject::m_components.size());
}

void DocEditor::init(GLManager *glManager)
{
  auto cam = std::make_shared<Entity>();
  cam->addComponent<OrthoCamera>(getEngine()->getWindow()->getWidth() / (float)getEngine()->getWindow()->getHeight(), 512, 0.01f, 10000.0f);
  addToScene(cam);

  auto primary_camera = cam->getComponent<OrthoCamera>();
  getEngine()->getGLManager()->setActiveCamera(primary_camera);

  auto go = std::make_shared<GameObject>();
  go->AddComponent<GameScriptedBehaviourTest>();
}

int main(int argc, char *argv[]) {
  DocEditor game;
  Engine gameEngine(&game, "Tests", glm::vec2(800,800));

  gameEngine.start();

  return 0;
}
