#pragma once
#include <string>
#include "HideFlags.hpp"
#include <vector>
#include <memory>
#include "Error.hpp"
#include <typeindex>
#include <typeinfo>
#include <unordered_map>
#include <set>

namespace mobagen {
  class Object {
  public:
    Object();

    virtual ~Object();

    /// \brief Should the object be hidden, saved with the scene or modifiable by the user?
    HideFlags hideFlags = HideFlags::None;

    /// \brief Returns the instance id of the object.
    uint64_t GetInstanceID();

    /// \brief Removes a gameobject, component or asset.
    static void Destroy(Object* obj);

    /// \brief Destroys the object obj immediately. You are strongly recommended to use Destroy instead.
    static void DestroyImmediate(Object *obj);

    /// \brief Makes the object target not be destroyed automatically when loading a new scene.
    static void DontDestroyOnLoad(std::shared_ptr<Object>);

    /// \brief Returns the first active loaded object of Type type.
    template<typename T>
    static T *FindObjectOfType();

    /// \brief Returns a list of all active loaded objects of Type type.
    template<typename T>
    static std::vector<T *> FindObjectsOfType();

    /// \brief Clones the object original and returns the clone.
    template<class T, class... _Types>
    static std::shared_ptr<T> Instantiate(_Types &&... _Args);

    /// \brief Compares two object references to see if they refer to the same object.
    inline bool operator==(const Object &other);

    /// \brief Compares if two objects refer to a different object.
    inline bool operator!=(const Object &other);

    // todo: check if this could be private
    inline bool operator<(const Object &other);

    inline bool operator<=(const Object &other);

    inline bool operator>(const Object &other);

    inline bool operator>=(const Object &other);

  private:
    // object id
    uint64_t _oid;
    static uint64_t _counter_;

    /// \brief container to store all objects
    static std::unordered_map<uint64_t, Object *> m_ObjectsById;
    static std::vector<std::shared_ptr<Object>> m_objects;

    static std::vector<Object *> m_ObjectsToBeDestroyed;
  };
}