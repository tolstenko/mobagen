#pragma once

#include <chrono>
#include "core/containers/types.hpp"

class Time {
public:
  static u64 MicroSecSinceMachineStart();
};