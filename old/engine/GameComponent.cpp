#include "GameComponent.hpp"
#include "GameObject.hpp"

namespace mobagen {
  void GameComponent::BroadcastMessage(std::string methodName, void *parameter, SendMessageOptions options) {
    gameObject->BroadcastMessage(methodName, parameter, options);
  }

  void GameComponent::BroadcastMessage(std::string methodName, SendMessageOptions options) {
    gameObject->BroadcastMessage(methodName, options);
  }

  bool GameComponent::CompareTag(std::string t) {
    return t.compare(tag) == 0;
  }

  template<typename T>
  T *GameComponent::GetComponent() {
    return gameObject->GetComponent<T>();
  }

  template<typename T>
  T *GameComponent::GetComponentInChildren() {
    return gameObject->GetComponentInChildren<T>();
  }

  template<typename T>
  T *GameComponent::GetComponentInParent() {
    return gameObject->GetComponentInParent<T>();
  }

  template<typename T>
  std::vector<T *> GameComponent::GetComponents() {
    return gameObject->GetComponents<T>();
  }

  template<typename T>
  std::vector<T *> GameComponent::GetComponentsInChildren() {
    return gameObject->GetComponentsInChildren<T>();
  }

  template<typename T>
  std::vector<T *> GameComponent::GetComponentsInParent() {
    return gameObject->GetComponentsInParent<T>();
  }

  void GameComponent::SendMessage(std::string methodName) {
    return gameObject->SendMessage(methodName);
  }

  void GameComponent::SendMessage(std::string methodName, void *value) {
    return gameObject->SendMessage(methodName, value);
  }

  void GameComponent::SendMessage(std::string methodName, void *value, SendMessageOptions options) {
    return gameObject->SendMessage(methodName, value, options);
  }

  void GameComponent::SendMessage(std::string methodName, SendMessageOptions options) {
    return gameObject->SendMessage(methodName, options);
  }

  void GameComponent::SendMessageUpwards(std::string methodName, SendMessageOptions options) {
    return gameObject->SendMessageUpwards(methodName, options);
  }

  void GameComponent::SendMessageUpwards(std::string methodName, void *value, SendMessageOptions options) {
    return gameObject->SendMessageUpwards(methodName, value, options);
  }

  std::shared_ptr<GameTransform> GameComponent::transform() {
    return gameObject->transform;
  }
}