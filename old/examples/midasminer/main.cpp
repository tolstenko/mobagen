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
#include "CrystalPicker.hpp"
#include "Crystal.hpp"
#include <SDL_main.h>
#include <iostream>
#include <map>
#include "Matrix.hpp"
#include <random>
#include "Menu.hpp"
#include "Input.hpp"


class CoolGame : public Game
{
public:
  virtual void init(GLManager *glManager);
  virtual void update(Input *input, std::chrono::microseconds delta);
};

void CoolGame::update(Input *input, std::chrono::microseconds delta)
{
  Game::update(input, delta);
}

void CoolGame::init(GLManager *glManager)
{
  getRootScene()->addComponent<Matrix>();
  
  // loat assets
  auto backgroundTex = std::make_shared<Texture>(Asset("BackGround.jpg"));
  auto normal = std::make_shared<Texture>(Asset("default_normal.jpg"));
  auto specular = std::make_shared<Texture>(Asset("default_specular.jpg"));

  std::map<Crystal::CrystalType, std::shared_ptr<Texture>> textures;
  textures[Crystal::CrystalType::BLUE]   = std::make_shared<Texture>(Asset("Blue.png"));
  textures[Crystal::CrystalType::GREEN]  = std::make_shared<Texture>(Asset("Green.png"));
  textures[Crystal::CrystalType::PURPLE] = std::make_shared<Texture>(Asset("Purple.png"));
  textures[Crystal::CrystalType::RED]    = std::make_shared<Texture>(Asset("Red.png"));
  textures[Crystal::CrystalType::YELLOW] = std::make_shared<Texture>(Asset("Yellow.png"));

  std::map<Crystal::CrystalType, std::shared_ptr<Material>> materials;
  materials[Crystal::CrystalType::BLUE]   = std::make_shared<Material>(textures[Crystal::CrystalType::BLUE], normal, specular);
  materials[Crystal::CrystalType::GREEN]  = std::make_shared<Material>(textures[Crystal::CrystalType::GREEN], normal, specular);
  materials[Crystal::CrystalType::PURPLE] = std::make_shared<Material>(textures[Crystal::CrystalType::PURPLE], normal, specular);
  materials[Crystal::CrystalType::RED]    = std::make_shared<Material>(textures[Crystal::CrystalType::RED], normal, specular);
  materials[Crystal::CrystalType::YELLOW] = std::make_shared<Material>(textures[Crystal::CrystalType::YELLOW], normal, specular);

  // store materials and textures
  getRootScene()->addComponent<CrystalPicker>(textures, materials);


  std::random_device rd;
  std::mt19937 gen(rd());
  std::uniform_int_distribution<> dis(0, 4);

  auto matrix = getRootScene()->getComponent<Matrix>();
  for(int y=0;y<8;y++){
    for(int x=0;x<8;x++){
	    auto color = (Crystal::CrystalType)dis(gen);
      auto entity = Crystal::CrystalFactory(textures,materials,x,y-8, color);
      auto crystal = entity->getComponent<Crystal>();
	    auto targetPosition = CrystalPicker::MatrixPositionToVec3(x, y);
	    crystal->dropTo(targetPosition);
	    matrix->setElement(x, y, crystal);
      addToScene(entity);
    }
  }

  auto backgroundMat = std::make_shared<Material>(backgroundTex, normal, specular);
  auto backgroundMesh = Plane::getMesh();
  auto planeEntity = std::make_shared<Entity>();
  planeEntity->addComponent<MeshRenderer>(backgroundMesh, backgroundMat);
  planeEntity->getTransform().setPosition(glm::vec3(0, 0, 0));
  planeEntity->getTransform().setScale(glm::vec3(755, 1, 600));
  addToScene(planeEntity);

  getRootScene()->addComponent<Menu>();

  auto cam = std::make_shared<Entity>();
  cam->addComponent<PerspectiveCamera>(glm::pi<float>() / 4.0f * 0.96f, getEngine()->getWindow()->getWidth() / (float)getEngine()->getWindow()->getHeight(), 0.01f, 10000.0f);
  cam->getTransform().setPosition(glm::vec3(0, getEngine()->getWindow()->getWidth(), 0));
  cam->getTransform().setScale(glm::vec3(0.8, 0.8, 0.8));
  cam->getTransform().setRotation(glm::quat(0, 0, 0.707, 0.707));
  cam->addComponent<DirectionalLight>(glm::vec3(1,1,1), 0.5);
  addToScene(cam);

  auto primary_camera = cam->getComponent<PerspectiveCamera>();
  getEngine()->getGLManager()->setActiveCamera(primary_camera);
}

int main(int argc, char *argv[]) {
  CoolGame game;
  Engine gameEngine(&game, "Midas Miner!", glm::vec2(755,600));
  gameEngine.getPhysicsManager()->setGravity(glm::vec3(0,0,0));

  gameEngine.start();

  return 0;
}
