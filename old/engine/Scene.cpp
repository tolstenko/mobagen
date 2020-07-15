#include "Scene.hpp"
#include "Error.hpp"

namespace mobagen {
  std::map<uint64_t, Object*> Scene::m_objects;
  std::map<uint64_t, GameComponent*> Scene::m_gameComponents;
  std::map<uint64_t, GameObject*> Scene::m_gameObjects;

  int Scene::rootCount() {
    throw NotImplementedException("SCENE rootCount");
    return 0;
  }

  bool Scene::IsValid() {
    throw NotImplementedException("SCENE IsValid");
    return false;
  }

  void Scene::GetRootGameObjects(std::vector<std::shared_ptr<GameObject>> *objs) {
//    objs = &rootGameObjects;
  }

  bool Scene::isDirty() {
    throw NotImplementedException("SCENE isDirty");
    return false;
  }

  bool Scene::isLoaded() {
    throw NotImplementedException("SCENE isLoaded");
    return false;
  }
}

