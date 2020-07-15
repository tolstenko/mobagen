#include "GameTransform.hpp"
#include "Error.hpp"

namespace mobagen {
  void GameTransform::SetParent(GameTransform *parent) {
    if (m_parent != nullptr) {
      // find itself on parent and remove itself
      m_parent->m_children.erase(this);
    }
    m_parent = parent;
    m_parent->m_children.emplace(this); // todo: check diff between insert
  }

  void GameTransform::DetachChildren() {
    for (auto x : m_children)
      x->m_parent = nullptr;
    m_children.clear();
  }

  void GameTransform::SetParent(GameTransform *parent, bool worldPositionStays) {
    throw GenericException();
  }
}