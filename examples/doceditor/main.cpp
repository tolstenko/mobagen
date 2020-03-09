#include "components/OrthoCamera.hpp"
#include "components/FreeLook.hpp"
#include "Mesh.hpp"
#include "Texture.hpp"
#include "Logger.hpp"
#include "Engine.hpp"
#include <map>
#include <networking/Request.hpp>


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
  std::string err = "http://dl5.webmfiles.org/big-buck-bunny_trailer.webm";
  std::string post = "https://www.httpbin.org/post";

  auto *request = new mobagen::networking::Request();
  request->setUrl(err);
  request->setMethod(HttpVerbEnum::GET);
  request->setHeaders(headers);
  request->onError = [](const std::shared_ptr<mobagen::networking::Response>& res){
    log_info("%d %s", res->status_code, res->error.message.c_str());
  };
  request->onSuccess = [](const std::shared_ptr<mobagen::networking::Response>& res){
    log_info("%d %s", res->status_code, res->text.c_str());
  };
  request->onUpdate = [](float progress){
    log_info("progress: %f", progress);
    return false;
  };
  request->send();
}

int main(int argc, char *argv[]) {
  DocEditor game;
  Engine gameEngine(&game, "DocEditor",glm::vec2(800,600));

  gameEngine.start();

  return 0;
}
