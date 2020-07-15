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
#include "EditorGUI.hpp"
#include <SDL_main.h>
#include <iostream>
#include <map>
#include <random>

class Uploader : public Game
{
public:
  virtual void init(GLManager *glManager);
  virtual void update(Input *input, std::chrono::microseconds delta);
};

void Uploader::update(Input *input, std::chrono::microseconds delta)
{
  Game::update(input, delta);
}

void Uploader::init(GLManager *glManager)
{
  // init editorgui
  getRootScene()->addComponent<EditorGUI>();
  getRootScene()->getComponent<EditorGUI>()->rootScene = getRootScene();

  auto cam = std::make_shared<Entity>();
  cam->addComponent<OrthoCamera>(getEngine()->getWindow()->getWidth() / (float)getEngine()->getWindow()->getHeight(), 512, 0.01f, 10000.0f);
  addToScene(cam);

  auto primary_camera = cam->getComponent<OrthoCamera>();
  getEngine()->getGLManager()->setActiveCamera(primary_camera);
}

int main(int argc, char *argv[]) {
  Uploader game;
  Engine gameEngine(&game, "UPLOADER", glm::vec2(800,400));

  gameEngine.start();

  return 0;
}
