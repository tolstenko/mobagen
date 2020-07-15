#include "Object.hpp"
#include "Error.hpp"
#include "Logger.hpp"
#include "GameComponent.hpp"

namespace mobagen {
  std::unordered_map<uint64_t, Object *> Object::m_ObjectsById;
  std::vector<Object *> Object::m_ObjectsToBeDestroyed;

  uint64_t Object::GetInstanceID() {
    return _oid;
  }

  Object::Object() : _oid(++_counter_) {
    m_ObjectsById[_oid] = this;
  }

  Object::~Object() = default;

  uint64_t Object::_counter_ = 0;

  void Object::Destroy(Object* obj) {
	auto gc = dynamic_cast<GameComponent*>(obj);
    
    // todo: create a manager to destroy at the end of the frame
    DestroyImmediate(obj);
  }

  void Object::DestroyImmediate(Object *obj) {
    if (m_ObjectsById.size() == 0) {
      delete (obj);
      obj = nullptr;
      return;
    }

    auto oid = obj->GetInstanceID();
    auto it = m_ObjectsById.find(oid);

    if (it != m_ObjectsById.end())
      m_ObjectsById.erase(it);

    delete (obj);
    obj = nullptr;
    // todo: check if object is component, if so, remove it from gameobject attached
  }

  void Object::DontDestroyOnLoad(std::shared_ptr<Object>) {
    throw NotImplementedException("Object DontDestroyOnLoad");
  }

  template<typename T>
  T *Object::FindObjectOfType() {
    // todo: find object by typeid instead of iterating over every object
    for (auto it = m_ObjectsById.begin(); it != m_ObjectsById.end(); it++) {
      auto item = dynamic_cast<T *>(it->second);
      if (item != nullptr)
        return item;
    }
    return nullptr;
  }

  template<typename T>
  std::vector<T *> Object::FindObjectsOfType() {
    std::vector<T *> ret;
    // todo: find object by typeid instead of iterating over every object
    for (auto it = m_ObjectsById.begin(); it != m_ObjectsById.end(); it++) {
      auto item = dynamic_cast<T *>(it->second);
      if (item != nullptr)
        ret.push_back(item);
    }
    return ret;
  }

  template<class T, class... _Types>
  std::shared_ptr<T> Object::Instantiate(_Types &&... _Args) {
    throw NotImplementedException("Object Instantiate");
    return nullptr;
  }

  bool Object::operator==(const Object &other) {
    // todo: improve this operator with type check, and make it tolerant to any type of object
    return _oid == other._oid;
  }

  bool Object::operator!=(const Object &other) {
    // todo: improve this operator with type check, and make it tolerant to any type of object
    return _oid != other._oid;
  }

  bool Object::operator<(const Object &other) {
    return _oid < other._oid;
  }

  bool Object::operator<=(const Object &other) {
    return _oid <= other._oid;
  }

  bool Object::operator>(const Object &other) {
    return _oid > other._oid;
  }

  bool Object::operator>=(const Object &other) {
    return _oid >= other._oid;
  }
}
