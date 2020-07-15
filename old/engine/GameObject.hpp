#pragma once
#include "Object.hpp"
#include "Transform.hpp"
#include "SendMessageOptions.hpp"
#include "PrimitiveType.hpp"
#include "GameTransform.hpp"
#include <type_traits>
#include <vector>

namespace mobagen {
  class GameObject : public Object, public std::enable_shared_from_this<GameObject> {
  public:
    explicit GameObject(std::string name = "");

    ~GameObject() override;

    /// The name of the gameObject.
    std::string name;

    /// Is the GameObject active in the scene?
    bool activeInHierarchy;

//  activeSelf	The local active state of this GameObject. (Read Only)
//  isStatic	Editor only API that specifies if a game object is static.

    /// The layer the game object is in. A layer is in the range [0...31].
    int layer;

//  scene	Scene that the GameObject is part of.
//  tag	The tag of this game object.

    /// The Transform attached to this GameObject.
    std::shared_ptr<GameTransform> transform;
   
    /// @brief Adds a component class named className to the game object.
	template<
		class T,
		class = std::enable_if_t<std::is_base_of<GameComponent,T>::value>
	>
    inline void AddComponent() {
	  //auto gc = std::make_shared<T>();
	  
      //gc.gameObject = shared_from_this();
      //m_components.push_back(gc);
    }

    /// \brief Calls the method named methodName on every MonoBehaviour in this game object or any of its children.
    void BroadcastMessage(std::string methodName, void *parameter = nullptr,
                          SendMessageOptions options = SendMessageOptions::RequireReceiver);

    /// \brief Calls the method named methodName on every MonoBehaviour in this game object or any of its children.
    void BroadcastMessage(std::string methodName, SendMessageOptions options = SendMessageOptions::RequireReceiver);

//  CompareTag	Is this game object tagged with tag ?

    /// @brief Returns the component of Type type if the game object has one attached, null if it doesn't.
    template<class T>
    inline std::shared_ptr<T> GetComponent() {
      // todo: improve velocity
      for (auto c:m_components) {
        auto gc = std::dynamic_pointer_cast<T>(c);
        if (gc != nullptr)
          return gc;
      }

      return nullptr;
    }

    /// \brief Returns the component of Type type in the GameObject or any of its children using depth first search.
    template<typename T>
    T *GetComponentInChildren();

    /// \brief Returns the component of Type type in the GameObject or any of its parents.
    template<typename T>
    T *GetComponentInParent();

    /// \brief Returns all components of Type type in the GameObject.
    template<typename T>
    std::vector<T *> GetComponents();

    /// \brief Returns all components of Type type in the GameObject or any of its children.
    template<typename T>
    std::vector<T *> GetComponentsInChildren();

    /// \brief Returns all components of Type type in the GameObject or any of its parents.
    template<typename T>
    std::vector<T *> GetComponentsInParent();

    /// \brief Calls the method named methodName on every MonoBehaviour in this game object.
    void SendMessage(std::string methodName);

    /// \brief Calls the method named methodName on every MonoBehaviour in this game object.
    void SendMessage(std::string methodName, void *value);

    /// \brief Calls the method named methodName on every MonoBehaviour in this game object.
    void SendMessage(std::string methodName, void *value, SendMessageOptions options);

    /// \brief Calls the method named methodName on every MonoBehaviour in this game object.
    void SendMessage(std::string methodName, SendMessageOptions options);

    /// \brief Calls the method named methodName on every MonoBehaviour in this game object and on every ancestor of the behaviour
    void SendMessageUpwards(std::string methodName, SendMessageOptions options = SendMessageOptions::RequireReceiver);

    /// \brief Calls the method named methodName on every MonoBehaviour in this game object and on every ancestor of the behaviour
    void SendMessageUpwards(std::string methodName, void *value = nullptr,
                            SendMessageOptions options = SendMessageOptions::RequireReceiver);

    /// \brief Activates/Deactivates the GameObject.
    void SetActive(bool value);

    /// \brief Creates a game object with a primitive mesh renderer and appropriate collider.
    static GameObject *CreatePrimitive(PrimitiveType type);

    /// \brief Finds a GameObject by name and returns it.
    static GameObject *Find(std::string name);

    /// \brief Returns a list of active GameObjects tagged tag. Returns empty array if no GameObject was found.
    static std::vector<GameObject *> FindGameObjectsWithTag(std::string tag);

    /// \brief Returns one active GameObject tagged tag. Returns null if no GameObject was found.
    static GameObject *FindWithTag(std::string tag);

    std::vector<std::shared_ptr<GameComponent>> m_components;
  private:
  };
}