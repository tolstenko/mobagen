#pragma once
#include "Object.hpp"
#include "SendMessageOptions.hpp"
#include <string>

namespace mobagen {
  class GameObject;
  class GameTransform;

  class GameComponent : public Object {
  public:
    /// \brief The game object this component is attached to. A component is always attached to a game object.
    std::shared_ptr<GameObject> gameObject;

    /// \brief The tag of this game object.
    std::string tag;

    /// \brief The Transform attached to this GameObject.
    std::shared_ptr<GameTransform> transform();

    /// \brief Calls the method named methodName on every MonoBehaviour in this game object or any of its children.
    void BroadcastMessage(std::string methodName, void *parameter = nullptr,
                          SendMessageOptions options = SendMessageOptions::RequireReceiver);

    /// \brief Calls the method named methodName on every MonoBehaviour in this game object or any of its children.
    void BroadcastMessage(std::string methodName, SendMessageOptions options = SendMessageOptions::RequireReceiver);

    /// \brief Is this game object tagged with tag ?
    bool CompareTag(std::string);

    /// \brief Returns the component of Type type if the game object has one attached, null if it doesn't.
    template<typename T>
    T *GetComponent();

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
  };
}