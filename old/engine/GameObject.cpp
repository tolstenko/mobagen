#include "GameObject.hpp"
#include "Error.hpp"
#include "GameComponent.hpp"
#include "Error.hpp"

namespace mobagen {
  GameObject::GameObject(std::string name) : Object(), std::enable_shared_from_this<GameObject>() {
    this->name = std::move(name);
    this->transform = std::make_shared<GameTransform>();
  }

  GameObject::~GameObject() = default;

  void GameObject::BroadcastMessage(std::string methodName, void *parameter, SendMessageOptions options) {
    throw NotImplementedException(typeid(this).name());
  }

  void GameObject::BroadcastMessage(std::string methodName, SendMessageOptions options) {
    throw NotImplementedException(typeid(this).name());
  }


  template<typename T>
  T *GameObject::GetComponentInChildren() {
    throw NotImplementedException("GameObject GetComponentInChildren");
  }

  template<typename T>
  std::vector<T *> GameObject::GetComponents() {
    throw NotImplementedException("GameObject GetComponents");
  }

  template<typename T>
  std::vector<T *> GameObject::GetComponentsInChildren() {
    throw NotImplementedException("GameObject GetComponents");
  }

  template<typename T>
  std::vector<T *> GameObject::GetComponentsInParent() {
    throw NotImplementedException("GameObject GetComponentsInParent");
  }


  void GameObject::SendMessage(std::string methodName) {
    throw NotImplementedException("GameObject SendMessage");
  }

  void GameObject::SendMessage(std::string methodName, void *value) {
    throw NotImplementedException("GameObject SendMessage");
  }

  void GameObject::SendMessage(std::string methodName, void *value, SendMessageOptions options) {
    throw NotImplementedException("GameObject SendMessage");
  }

  void GameObject::SendMessage(std::string methodName, SendMessageOptions options) {
    throw NotImplementedException("GameObject SendMessage");
  }

  void GameObject::SendMessageUpwards(std::string methodName, SendMessageOptions options) {
    throw NotImplementedException("GameObject SendMessageUpwards");
  }

  void GameObject::SendMessageUpwards(std::string methodName, void *value, SendMessageOptions options) {
    throw NotImplementedException("GameObject SendMessageUpwards");
  }

  void GameObject::SetActive(bool value) {
    throw NotImplementedException("GameObject SetActive");
  }

  GameObject *GameObject::CreatePrimitive(PrimitiveType type) {
    throw NotImplementedException("GameObject CreatePrimitive");
  }

  GameObject *GameObject::Find(std::string name) {
    throw NotImplementedException("GameObject Find");
  }

  std::vector<GameObject *> GameObject::FindGameObjectsWithTag(std::string tag) {
    throw NotImplementedException("GameObject FindGameObjectsWithTag");
  }

  GameObject *GameObject::FindWithTag(std::string tag) {
    throw NotImplementedException("GameObject FindWithTag");
  }

  template<typename T>
  T *GameObject::GetComponentInParent() {
    throw NotImplementedException("GameObject GetComponentInParent");
  }
}