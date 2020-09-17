#include "Time.hpp"

u64 Time::MicroSecSinceMachineStart() {
  u64 ms = std::chrono::duration_cast<std::chrono::microseconds>(
      std::chrono::steady_clock::now().time_since_epoch()
  ).count();
  return ms;
}
