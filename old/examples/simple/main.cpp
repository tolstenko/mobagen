#include "components/MeshRenderer.hpp"
#include "components/PerspectiveCamera.hpp"
#include "components/OrthoCamera.hpp"
#include "components/FreeMove.hpp"
#include "components/FreeLook.hpp"
#include "components/DirectionalLight.hpp"
#include "components/SpotLight.hpp"
#include "components/PointLight.hpp"
#include "components/SphereCollider.hpp"
#include "SimpleBehaviour.h"

#include "Plane.hpp"
#include "Mesh.hpp"
#include "GLManager.hpp"
#include "Texture.hpp"
#include "Logger.hpp"
#include "Game.hpp"
#include "MeshLoader.hpp"
#include "Engine.hpp"
#include <SDL_main.h>
#include <iostream>
#include <map>
#include <random>

using namespace mobagen;

class Simple : public Game
{
public:
	virtual void init(GLManager *glManager);
    virtual void update(Input *input, std::chrono::microseconds delta);
};

void Simple::update(Input *input, std::chrono::microseconds delta)
{
	Game::update(input, delta);
}

void Simple::init(GLManager *glManager)
{
	auto cam = std::make_shared<Entity>();
	cam->addComponent<OrthoCamera>(getEngine()->getWindow()->getWidth() / (float)getEngine()->getWindow()->getHeight(), 512, 0.01f, 10000.0f);
	addToScene(cam);

	auto primary_camera = cam->getComponent<OrthoCamera>();
	getEngine()->getGLManager()->setActiveCamera(primary_camera);

    getRootScene()->addComponent<SimpleBehaviour>();
}

int main(int argc, char *argv[]) {
	Simple game;
	Engine gameEngine(&game, "Simple Test", glm::vec2(800,600));

	gameEngine.start();

	return 0;
}
