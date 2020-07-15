#pragma once
#include "GameComponent.hpp"

namespace mobagen {
  class Behaviour : public GameComponent {

  public:
    /// @brief Enabled Behaviours are Updated, disabled Behaviours are not.
    bool enabled = false;

    /// @brief 	Has the Behaviour had enabled called.
    bool isActiveAndEnabled = false;
  };
}