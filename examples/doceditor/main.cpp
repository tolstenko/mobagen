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
#include <networking/Request.hpp>
#include "WebRequest.hpp"

using namespace mobagen;

class DocEditor : public Game
{
public:
  virtual void init(GLManager *glManager);
  virtual void update(Input *input, std::chrono::microseconds delta);
};

void DocEditor::update(Input *input, std::chrono::microseconds delta)
{
  Game::update(input, delta);
}

void DocEditor::init(GLManager *glManager)
{
  auto cam = std::make_shared<Entity>();
  cam->addComponent<OrthoCamera>(getEngine()->getWindow()->getWidth() / (float)getEngine()->getWindow()->getHeight(), 512, 0.01f, 10000.0f);
  cam->getTransform().setPosition(glm::vec3(0, 512, 0));
  cam->getTransform().setScale(glm::vec3(1, 1, 1));
  cam->getTransform().setRotation(glm::quat(0, 0, 0.707, 0.707));
  addToScene(cam);

  auto primary_camera = cam->getComponent<OrthoCamera>();
  getEngine()->getGLManager()->setActiveCamera(primary_camera);

  std::map<std::string, std::string> headers = {{"tolsta","tolsta"},{"Content-Type", "text/plain"}};
  std::string body = "this is raw data";
  std::string get = "https://www.httpbin.org/get";
  std::string post = "https://www.httpbin.org/post";

  auto request = new mobagen::networking::Request();
  request->setUrl(get);
  request->setMethod(HttpVerbEnum::GET);
  request->setHeaders(headers);
  request->send();

  WebRequest::Get(get,headers,[](const std::string& err, const std::string& res){
    log_info("%s",err.c_str());
    log_info("%s",res.c_str());
  });

  WebRequest::Post(post,headers,body,[](const std::string& err, const std::string& res){
    log_info("%s",err.c_str());
    log_info("%s",res.c_str());
  });
}

int main(int argc, char *argv[]) {
  DocEditor game;
  Engine gameEngine(&game, "DocEditor",glm::vec2(800,600));

  gameEngine.start();

  return 0;
}
