#pragma once
#include <string>
#include "GameObject.hpp"
#include <map>

namespace mobagen {
  class Scene {
  public:
    /// @brief Returns the index of the scene in the Build Settings. Always returns -1 if the scene was loaded through an AssetBundle.
    int buildIndex = -1;

    /// @brief Returns true if the scene is modifed.
    bool isDirty();

    /// @brief Returns true if the scene is loaded.
    bool isLoaded();

    /// @brief Returns the name of the scene.
    std::string name;

    /// @brief Returns the relative path of the scene. Like: "Assets/MyScenes/MyScene.unity".
    std::string path;

    /// @brief The number of root transforms of this scene.
    int rootCount();

    /// @brief Returns all the root game objects in the scene.
    void GetRootGameObjects(std::vector<std::shared_ptr<GameObject>> *);

    /// @brief Whether this is a valid scene. A scene may be invalid if, for example, you tried to open a scene that does not exist. In this case, the scene returned from EditorSceneManager.OpenScene would return False for IsValid.
    bool IsValid();

  private:
    static std::vector<GameObject*> rootGameObjects;
	static std::map<uint64_t, Object*> m_objects;
	static std::map<uint64_t, GameComponent*> m_gameComponents;
	static std::map<uint64_t, GameObject*> m_gameObjects;
  };
}